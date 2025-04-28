#include <android/androidresourceloader.h>
#include <android/glesrenderer.h>

#include <engine.h>
#include <jni.h>
#include <utils.h>

extern "C" {

namespace {
void solve(Geometry::VolumePuzzle* puzzle) {
    Geometry::Solver solver(*puzzle);
    solver.solve();
}  // namespace
Geometry::VolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
std::shared_ptr<Engine> engine;
std::mutex m;
float lstart;
}  // namespace

JNIEXPORT void JNICALL
    Java_com_gittopper_puzzle_NativeLibrary_init(JNIEnv* env,
                                                 jobject obj,
                                                 jint width,
                                                 jint height,
                                                 jobject javaAssetManager) {
    std::lock_guard<std::mutex> lock(m);
    auto res = std::make_shared<AndroidResourceLoader>(
        AAssetManager_fromJava(env, javaAssetManager));
    engine =
        std::make_shared<Engine>(puzzle, std::make_shared<GLESRenderer>(), res);
    engine->setup();
    engine->resize(width, height);
}

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_dragStart(
    JNIEnv* env, jobject obj, jint x1, jint y1, jint x2, jint y2) {
    std::lock_guard<std::mutex> lock(m);
    lstart = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float x = (x1 + x2) * 0.5;
    float y = (y1 + y2) * 0.5;
    engine->shiftStart(x, y);
}

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_drag(
    JNIEnv* env, jobject obj, jint x1, jint y1, jint x2, jint y2) {
    std::lock_guard<std::mutex> lock(m);
    float l = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    engine->zoom(lstart / l );
    float x = (x1 + x2) * 0.5;
    float y = (y1 + y2) * 0.5;
    engine->drag(x, y);
}

JNIEXPORT void JNICALL
    Java_com_gittopper_puzzle_NativeLibrary_dragStop(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    engine->dragStop();
}

JNIEXPORT void JNICALL
    Java_com_gittopper_puzzle_NativeLibrary_step(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    engine->display();
}

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_moveStart(
    JNIEnv* env, jobject obj, jint x, jint y) {
    std::lock_guard<std::mutex> lock(m);
    engine->rotateStart(x, y);
}

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_move(JNIEnv* env,
                                                                    jobject obj,
                                                                    jint x,
                                                                    jint y) {
    std::lock_guard<std::mutex> lock(m);
    engine->drag(x, y);
}

}  // namespace
