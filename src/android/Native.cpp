/* Copyright (c) 2013-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <jni.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "renderer.h"
#include <utils.h>
#include <solver.h>
#include <volpartrenderer.h>
#include <piecessetrenderer.h>
#include <thread>


extern "C"
{
    JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_init(
            JNIEnv * env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_dragStart(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2);
    JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_drag(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2);
JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_dragStop(
        JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_step(
            JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_moveStart(
        JNIEnv * env, jobject obj, jint x, jint y);
JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_move(
        JNIEnv * env, jobject obj, jint x, jint y);
};

namespace
{
    void solve(Geometry::VolumePuzzle* puzzle)
    {
        Geometry::Solver solver(*puzzle);
        solver.solve();
    }
}
Geometry::VolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
std::thread st(solve, &puzzle);
auto renderer = std::make_shared<Renderer>();
auto volpart_renderer =std::make_shared<VolPartRenderer>(renderer);
PiecesSetRenderer pieces_renderer(volpart_renderer);
int found_solutions = 0;
std::mutex m;

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_init(
        JNIEnv * env, jobject obj, jint width, jint height)
{
    std::lock_guard<std::mutex> lock(m);
    renderer->setup();
    renderer->setSize(width, height);
}

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_step(
        JNIEnv * env, jobject obj)
{
    std::lock_guard<std::mutex> lock(m);
    renderer->startFrame();

    Geometry::PiecesSet sol;
    int ns = puzzle.numFoundSolutions();
    if (ns > found_solutions)
    {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "found solution %d", ns);
        found_solutions = ns;
    }
    puzzle.getSolution(sol, ns);

    pieces_renderer.render(sol);

}

float lstart;

float move_start_x;
float move_start_y;

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_dragStart(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
    std::lock_guard<std::mutex> lock(m);
    lstart = std::sqrt((x2 - x1) * (x2 - x1)+ (y2 - y1) * (y2 - y1));
    move_start_x = (x1 + x2) * 0.5;
    move_start_y = (y1 + y2) * 0.5;
}

JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_dragStop(
        JNIEnv * env, jobject obj)
{
    std::lock_guard<std::mutex> lock(m);
    renderer->camera().store();
}
JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_drag(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
    std::lock_guard<std::mutex> lock(m);
    float l = std::sqrt((x2 - x1) * (x2 - x1)+ (y2 - y1) * (y2 - y1));
    renderer->camera().zoom((l - lstart) / 100);
    float x = (x1 + x2) * 0.5;
    float y = (y1 + y2) * 0.5;
    renderer->camera().setShift((x - move_start_x) / 100, (move_start_y - y) / 100);
}


JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_moveStart(
        JNIEnv * env, jobject obj, jint x, jint y) {
    std::lock_guard<std::mutex> lock(m);
    move_start_x = x;
    move_start_y = y;
}
JNIEXPORT void JNICALL Java_com_gittopper_puzzle_NativeLibrary_move(
        JNIEnv * env, jobject obj, jint x, jint y) {
    std::lock_guard<std::mutex> lock(m);
    renderer->camera().setAngles((y - move_start_y) / 10,(x - move_start_x) / 10);
}
