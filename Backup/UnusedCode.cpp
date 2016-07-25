// UnusedCode
// Might be useful later?  Saving here just in case.
#if false

float MotionSystemImpl::getEllapsedTimeInSeconds()
{
	TimePoint currentTime;
	GetTime(currentTime.hour, currentTime.min, currentTime.sec);

	int deltaHour;
	if (currentTime.hour < previousTime.hour) {
		// Time went past 11 hour max
		deltaHour = (12 - previousTime.hour) + currentTime.hour;
	}
	else {
		deltaHour = currentTime.hour - previousTime.hour;
	}

	int deltaMin;
	if (currentTime.min < previousTime.min) {
		// Time went past 59 min max
		deltaMin = (60 - previousTime.min) + currentTime.min;
	}
	else {
		deltaMin = currentTime.min - previousTime.min;
	}

	int deltaSec;
	if (currentTime.sec < previousTime.sec) {
		// Time went past 59 sec max
		deltaSec = (60 - previousTime.sec) + currentTime.sec;
	}
	else {
		deltaSec = currentTime.sec - previousTime.sec;
	}

	float result = static_cast<float>(deltaHour * 3600 + deltaMin * 60 + deltaSec);

	previousTime = currentTime;
	return result;
}

#endif