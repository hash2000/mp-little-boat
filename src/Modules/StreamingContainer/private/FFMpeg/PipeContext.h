#pragma once
#include "hardware.h"
#include "FFMpegError.h"
#include <string>
#include <list>

class PipeContext
{
public:

	void SetMesssage(const std::string& message);

	void SetFile(const std::string& file);

	void SetInputFormatName(const std::string& name);

	void SetInputFormat(const AVInputFormat* set);

	void SetFormatContext(AVFormatContext* set);

	void SetCodec(const AVCodec* codec, AVMediaType type);

	void SetStream(AVStream* stream, AVMediaType type);

	void SetCodecContext(AVCodecContext* context, AVMediaType type);

	void SetHardwareContext(AVBufferRef* context, AVMediaType type);

	void SetBuffering(int set);

	void SetFFMpegOpts(const std::string& opts);

	void SetMaxLuminance(uint16_t set, AVMediaType type);

	void UseReconnecting(bool set);

	void UseHardwareDecode(bool set, AVMediaType type);

	const std::list<std::string>& GetMessages() const;

	bool IsCached() const;

	bool IsLocalFile() const;

	bool IsReconnectiong() const;

	bool IsHardwareDecode(AVMediaType type) const;

	int GetBuffering() const;

	uint16_t GetMaxLuminance(AVMediaType type) const;

	const AVInputFormat* GetInputFormat() const;

	AVFormatContext* GetFormatContext() const;

	std::string GetFile() const;

	std::string GetInputFormatName() const;

	std::string GetFFMpegOpts() const;

	const AVCodec* GetCodec(AVMediaType type) const;

	AVStream* GetStream(AVMediaType type) const;

	AVCodecContext* GetCodecContext(AVMediaType type) const;

	AVBufferRef* GetHardwareContext(AVMediaType type) const;

private:
	struct {
		std::string _file;
		std::string _format = "mp4";
		std::string _ffmpegOpts;
		int _buffering = 1024;
		bool _reconnecting = true;
		bool _isFullDecode = true;
		bool _isLocalFile = false;
		const AVInputFormat* _inputFormat = nullptr;
		AVFormatContext* _formatContext = nullptr;
	} _input;

	struct {
		uint16_t _maxLuminance = 0;
		bool _hardware = true;
		const AVCodec* _codec = nullptr;
		AVStream* _stream = nullptr;
		AVCodecContext* _context = nullptr;
		AVBufferRef* _hardwareContext = nullptr;
	} _video, _audio;

	std::list<std::string> _messages;
};
