#include "_stodin_lib_sdl.h"

namespace _stodin_lib_sdl
{
    void init(uint32_t flags)
    {
        if(SDL_Init(flags) < 0)
            throw runtime_error("SDL init error!");
    }
    
    void set_hint(__stodin_string name, __stodin_string value)
    {
        SDL_SetHint(name.get_string().c_str(), value.get_string().c_str());
    }
    
    void create_window(Window & window, __stodin_string title, int64_t x, int64_t y, int64_t w, int64_t h, uint32_t flags)
    {
        window = SDL_CreateWindow(title.get_string().c_str(), static_cast<int>(x), static_cast<int>(y), 
            static_cast<int>(w), static_cast<int>(h), flags);
        if(window == NULL)
            throw runtime_error("Window creating error!");
    }
    
    void create_renderer(Renderer & renderer, Window & window, int64_t index, uint32_t flags)
    {
        renderer = SDL_CreateRenderer(window, static_cast<int>(index), flags);
        if(renderer == NULL)
            throw runtime_error("Renderer creating error!");
        
    }
    
    void set_render_draw_color(Renderer & renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
    
    void render_clear(Renderer & renderer)
    {
        SDL_RenderClear(renderer);
    }
    
    void render_fill_rect(Renderer & renderer, SDL_Rect & rect)
    {
        SDL_RenderFillRect(renderer, &rect );
    }
    
    void render_draw_rect(Renderer & renderer, SDL_Rect & rect)
    {
        SDL_RenderDrawRect(renderer, &rect);
    }
    
    void render_draw_line(Renderer & renderer, int64_t x1, int64_t y1, int64_t x2, int64_t y2)
    {
        SDL_RenderDrawLine(renderer, static_cast<int>(x1), static_cast<int>(y1),
                                     static_cast<int>(x2), static_cast<int>(y2));
    }
    
    void render_draw_point(Renderer & renderer, int64_t x, int64_t y)
    {
        SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
    }
    
    void render_present(Renderer & renderer)
    {
        SDL_RenderPresent(renderer);
    }
    
    void poll_event(int64_t & res, Event & event)
    {
        res = static_cast<int64_t>(SDL_PollEvent(&event));
    }
    
    void get_mouse_state(uint32_t & bitmask, int64_t & x, int64_t & y)
    {
        int xx = 0;
        int yy = 0;
        bitmask = SDL_GetMouseState(&xx, &yy);
        x = static_cast<int64_t>(xx);
        y = static_cast<int64_t>(yy);
    }
    
    void show_simple_message_box(uint32_t flags, __stodin_string title, __stodin_string message)
    {
        SDL_ShowSimpleMessageBox(flags, title.get_string().c_str(), message.get_string().c_str(), NULL);
    }

    
    void delay(int64_t t)
    {
        SDL_Delay(static_cast<uint32_t>(t));
    }
    
    void destroy_renderer(Renderer & renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    void destroy_window(Window & window)
    {
        SDL_DestroyWindow(window);
    }
    void quit()
    {
        SDL_Quit();
    }
    
    
}