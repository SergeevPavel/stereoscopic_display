// TestCPPLibrary.h

extern "C" {
	__declspec(dllexport) int initController();
	__declspec(dllexport) int deinitController();
    __declspec(dllexport) float getVerticalAngle();
	__declspec(dllexport) float getHorizontalAngle();
}