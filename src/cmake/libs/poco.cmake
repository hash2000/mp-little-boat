message(STATUS "Find Poco REQUIRED")

find_package(Poco
    CONFIG REQUIRED COMPONENTS
        Foundation
        XML
        JSON
        Util
        Data
        Net
		NetSSL
        Crypto
        JWT
        Encodings
)
