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

	void SetBuffering(int set);

	void SetFFMpegOpts(const std::string& opts);

	void SetReconnecting(bool set);

	const std::list<std::string>& GetMessages() const;

	bool IsCached() const;

	bool IsLocalFile() const;

	bool IsReconnectiong() const;

	int GetBuffering() const;

	const AVInputFormat* GetInputFormat() const;

	AVFormatContext* GetFormatContext() const;

	std::string GetFile() const;

	std::string GetInputFormatName() const;

	std::string GetFFMpegOpts() const;

private:
	struct {
		std::string _file;
		std::string _format = "mp4";
		std::string _ffmpegOpts;
		int _buffering = 1024;
		bool _reconnecting = true;
	} _params;

	std::list<std::string> _messages;
	bool _isFullDecode = true;
	bool _isLocalFile = false;
	const AVInputFormat* _inputFormat = nullptr;
	AVFormatContext* _formatContext = nullptr;
};
