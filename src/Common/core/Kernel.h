#pragma once
#include <typeindex>
#include <string>
#include <map>
#include <list>
#include <memory>

namespace Ioc {

	class Kernel;

	class ITypeFactory
	{
	public:
		virtual ~ITypeFactory() {
		}

		virtual const std::type_info& GetType() const = 0;

		virtual std::shared_ptr<void> CreateItem(const Kernel& kernel) = 0;
	};

	template<typename T>
	class BaseTypeFactory : public ITypeFactory
	{
	private:
		virtual std::shared_ptr<void> InternalCreateItem(const Kernel& kernel) = 0;

	public:
		BaseTypeFactory()
			: ITypeFactory() {
		}

		~BaseTypeFactory() {
		}

		const std::type_info& GetType() const override {
			return typeid(T);
		}

		std::shared_ptr<void> CreateItem(const Kernel& kernel) override {
			return InternalCreateItem(kernel);
		}
	};

	template<typename T>
	class InstanceTypeFactory : public BaseTypeFactory<T>
	{
	private:
		std::shared_ptr<T> _instance;

		std::shared_ptr<void> InternalCreateItem(const Kernel& kernel) override {
			return _instance;
		}

	public:
		InstanceTypeFactory(std::shared_ptr<T> instance)
			: BaseTypeFactory<T>()
			, _instance(instance) {
		}

		~InstanceTypeFactory() {
		}
	};


	template<size_t index>
	struct RecursiveResolveImpl;

	template<>
	struct RecursiveResolveImpl<0>
	{
		template<typename resolver_type, typename T, typename callable_type>
		static std::shared_ptr<void> Resolve(const Kernel& kernel, resolver_type& resolver, callable_type callable)
		{
			return std::static_pointer_cast<T>(callable(kernel));
		}
	};

	template<size_t i>
	struct RecursiveResolveImpl
	{
		template<typename resolver_type, typename T,
			typename callable_type, typename ...argtypes>
		static std::shared_ptr<void> Resolve(const Kernel& kernel, resolver_type& resolver, callable_type callable)
		{
			return callable(kernel, resolver.template Resolve<argtypes>()...);
		}
	};

	struct RecursiveResolve
	{
		template<typename T, typename resolver_type,
			typename callable_type, typename ...argtypes>
		static std::shared_ptr<void> Resolve(const Kernel& kernel, resolver_type& resolver, callable_type callable)
		{
			return RecursiveResolveImpl<sizeof...(argtypes)>
				::template Resolve<resolver_type, T, callable_type, argtypes...>(kernel, resolver, callable);
		}
	};

	template<typename I, typename T, typename ...argtypes>
	class ResolvableFactory
		: public BaseTypeFactory<T>
	{
	private:
		static std::shared_ptr<void> Creator(const Kernel& kernel, std::shared_ptr<argtypes>... args)
		{
			return std::make_shared<T>(kernel, args...);
		}

		std::shared_ptr<void> InternalCreateItem(const Kernel& kernel) override
		{
			std::shared_ptr<void> result = RecursiveResolve
				::Resolve<T, const Kernel, std::shared_ptr<void>(*)(const Kernel&, std::shared_ptr<argtypes>...), argtypes...>
					(kernel, kernel, ResolvableFactory::Creator);
			return result;
		}

	public:
		ResolvableFactory()
			: BaseTypeFactory<T>()
		{
		}

		~ResolvableFactory()
		{
		}
	};

	template<typename I, typename T, typename ...argtypes>
	class ScopedResolvableFactory
		: public BaseTypeFactory<T>
	{
	private:
		std::shared_ptr<void> _instance;

	private:
		static std::shared_ptr<void> Creator(const Kernel& kernel, std::shared_ptr<argtypes>... args)
		{
			return std::make_shared<T>(kernel, args...);
		}

		std::shared_ptr<void> InternalCreateItem(const Kernel& kernel) override
		{
			if (_instance.get() == nullptr) {
				_instance =	RecursiveResolve
					::Resolve<T, const Kernel, std::shared_ptr<void>(*)(const Kernel&, std::shared_ptr<argtypes>...), argtypes...>
						(kernel, kernel, ScopedResolvableFactory::Creator);
			}
			return _instance;
		}

	public:
		ScopedResolvableFactory()
			: BaseTypeFactory<T>()
		{
		}

		~ScopedResolvableFactory()
		{
		}
	};

	class Kernel
	{
	private:
		template<typename T>
		struct EllidedDeleter {
			void operator()(T* val) {
				// empty
			}
		};

		using KernelDeleter = EllidedDeleter<Kernel>;
		using TypesList = std::map<std::type_index, std::shared_ptr<ITypeFactory>>;

		TypesList _types;
		std::shared_ptr<Kernel> _self;

		template<typename F, typename I, typename T, typename ...argtypes>
		void AddTypeHelper(argtypes... args)
		{
			std::shared_ptr<ITypeFactory> factory;
			std::type_index i(typeid(I));
			std::type_index a(typeid(T));

			const auto& ita = _types.find(a);
			if (ita == _types.end()) {
				factory = std::make_shared<F>(args...);
				_types[a] = factory;
			}
			else {
				factory = ita->second;
			}

			const auto& iti = _types.find(i);
			if (i != a && iti == _types.end()) {
				_types[i] = factory;
			}
		}

		template<typename T>
		const std::shared_ptr<ITypeFactory> ResolveFactory() const
		{
			// Lookup interface type. If it cannot be found return
			// the default for that type.
			std::shared_ptr<ITypeFactory> result;
			TypesList::const_iterator i = _types.find(std::type_index(typeid(T)));
			if (i != _types.end()) {
				result = i->second;
			}
			return result;
		}

	public:
		Kernel()
			: _self(this, KernelDeleter())
		{
			this->AddInstance<Kernel>(_self);
		}

		~Kernel()
		{
			_types.clear();
			_self.reset();
		}

		template<typename T>
		void AddInstance(std::shared_ptr<T> instance) {
			using factoryType = InstanceTypeFactory<T>;
			this->AddTypeHelper<factoryType, T, std::shared_ptr<T>>(instance);
		}

		template<typename T, typename ...argtypes>
		void AddTransient() {
			using factoryType = ResolvableFactory<T, T, argtypes...>;
			this->AddTypeHelper<factoryType, T, T>();
		}

		template<typename I, typename T, typename ...argtypes>
		void AddTransientAbstraction() {
			using factoryType = ResolvableFactory<I, T, argtypes...>;
			this->AddTypeHelper<factoryType, I, T>();
		}

		template<typename T, typename ...argtypes>
		void AddScoped() {
			using factoryType = ScopedResolvableFactory<T, T, argtypes...>;
			this->AddTypeHelper<factoryType, T, T>();
		}

		template<typename I, typename T, typename ...argtypes>
		void AddScopedAbstraction() {
			using factoryType = ScopedResolvableFactory<I, T, argtypes...>;
			this->AddTypeHelper<factoryType, I, T>();
		}

		template<typename T>
		std::shared_ptr<T> Resolve() const
		{
			std::shared_ptr<T> result = nullptr;
			const auto factory = ResolveFactory<T>();
			if (factory)
			{
				result = std::static_pointer_cast<T>(factory->CreateItem(*this));
			}

			return result;
		}
	};

}
