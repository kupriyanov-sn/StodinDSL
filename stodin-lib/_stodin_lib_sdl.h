#ifndef _STODIN_LIB_SDL_H
#define _STODIN_LIB_SDL_H

#include <cstdint>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // _WIN32

#include "__stodin_string.h"

namespace _stodin_lib_sdl
{
    typedef ::SDL_Window* Window;
    typedef ::SDL_Renderer* Renderer;
    typedef ::SDL_Event Event;
    extern void init(uint32_t flags);
    extern void set_hint(__stodin_string name, __stodin_string value);
    extern void create_window(Window & window, __stodin_string title, int64_t x, int64_t y, int64_t w, int64_t h, uint32_t flags);
    extern void create_renderer(Renderer & renderer, Window & window, int64_t index, uint32_t flags);
    extern void set_render_draw_color(Renderer & renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    extern void render_clear(Renderer & renderer);
    extern void render_fill_rect(Renderer & renderer, SDL_Rect & rect);
    extern void render_draw_rect(Renderer & renderer, SDL_Rect & rect);
    extern void render_draw_line(Renderer & renderer, int64_t x1, int64_t y1, int64_t x2, int64_t y2);
    extern void render_draw_point(Renderer & renderer, int64_t x, int64_t y);
    extern void render_present(Renderer & renderer);
    extern void poll_event(int64_t & res, Event & event);
    extern void get_mouse_state(uint32_t & bitmask, int64_t & x, int64_t & y);
    extern void show_simple_message_box(uint32_t flags, __stodin_string title, __stodin_string message);
    extern void delay(int64_t t);
    extern void destroy_renderer(Renderer & renderer);
    extern void destroy_window(Window & window);
    extern void quit();
}

#endif // _STODIN_LIB_SDL_H
