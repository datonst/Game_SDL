#pragma once
#ifndef Timer_
#define TImer_
#include <iostream>
#include "CommonFunction.h"
class ImpTimer
{
public:
	ImpTimer();
	void start();
	void stop();
	void pause();
	void unpause();
	int get_ticks();
	bool is_started();
	bool is_paused();

private:
	//time at started
	int start_tick_;
	//The ticks stored when the timer was paused
	int paused_ticks_;
	bool is_paused_;
	bool is_started_;

};

#endif
