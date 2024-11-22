#include "MainWindowFFMpeg.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>



MainWindowFFMpeg::MainWindowFFMpeg(const char* label)
	: Fl_Double_Window(800, 600, label)
{
	InitializeFFMpeg();

	auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert };
	fl->margin(Margin{ 20 });
	fl->SetLayoutStrategy(LayoutStrategy::Full);
	{

		fl->end();
	}
}


void MainWindowFFMpeg::pgm_save(unsigned char* buf, int wrap, int xsize, int ysize,
	const char* filename)
{
	FILE* f;
	int i;

	f = fopen(_pathDecoded.c_str(), "wb");
	fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
	for (i = 0; i < ysize; i++)
		fwrite(buf + i * wrap, 1, xsize, f);
	fclose(f);
}


void MainWindowFFMpeg::decode(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt)
{
	char buf[1024];
	int ret;

	ret = avcodec_send_packet(dec_ctx, pkt);
	if (ret < 0) {
		fprintf(stderr, "Error sending a packet for decoding\n");
		exit(1);
	}

	while (ret >= 0) {
		ret = avcodec_receive_frame(dec_ctx, frame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			return;
		else if (ret < 0) {
			fprintf(stderr, "Error during decoding\n");
			exit(1);
		}

		printf("saving frame %3lld\n", dec_ctx->frame_num);
		fflush(stdout);

		/* the picture is allocated by the decoder. no need to
		   free it */
		snprintf(buf, sizeof(buf), "%s-%lld", _pathDecoded.c_str(), dec_ctx->frame_num);
		pgm_save(frame->data[0], frame->linesize[0],
			frame->width, frame->height, buf);
	}
}

void MainWindowFFMpeg::InitializeFFMpeg()
{
	AVFormatContext* pFormatContext = avformat_alloc_context();
	avformat_open_input(&pFormatContext, _path.c_str(), nullptr, nullptr);
	avformat_find_stream_info(pFormatContext, nullptr);

	for (unsigned int nstream = 0; nstream < pFormatContext->nb_streams; nstream++)
	{
		AVCodecParameters* pLocalCodecParameters = pFormatContext->streams[nstream]->codecpar;
		const AVCodec* pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
		if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
			std::printf("Video Codec: resolution %d x %d\n", pLocalCodecParameters->width, pLocalCodecParameters->height);
		}
		else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
			std::printf("Audio Codec: sample rate %d\n", pLocalCodecParameters->sample_rate);
		}

		// general
		std::printf("\tCodec %s ID %d bit_rate %lld\n", pLocalCodec->long_name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
	}


}
