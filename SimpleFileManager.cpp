#define SFM_CLI

#ifdef SFM_CLI
#include "CLI/start.cpp"
// #endif // SFM_CLI
#else
#include "VISUAL/start.cpp"
#endif // SFM_CLI

int main() {
	start();
}
