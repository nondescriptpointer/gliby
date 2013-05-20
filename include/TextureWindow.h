#pragma once

#include <GL/glew.h>
#include <vector>
#include "berkelium/Window.hpp"
#include "berkelium/WindowDelegate.hpp"
#include "berkelium/Context.hpp"
#include "berkelium/ScriptUtil.hpp"
#include <jsoncpp/json/json.h>

namespace gliby {

struct CallbackHandler {
    Berkelium::WideString funcName; 
    void (*func)(Json::Value* root);
};

class TextureWindow : public Berkelium::WindowDelegate {
    public:
        TextureWindow(unsigned int w, unsigned int h, bool transp, bool verb = false);
        ~TextureWindow(void);

        Berkelium::Window* window(void) const;
        GLuint texture(void) const;

        void clear(void);

        virtual void onPaint(Berkelium::Window* win, const unsigned char* bitmap_in, const Berkelium::Rect &bitmap_rect,
            size_t num_copy_rects, const Berkelium::Rect* copy_rects, int dx, int dy, const Berkelium::Rect &scroll_rect);

        virtual void onAddressBarChanged(Berkelium::Window *win, Berkelium::URLString newURL);
        virtual void onStartLoading(Berkelium::Window *win, Berkelium::URLString newURL);
        virtual void onLoad(Berkelium::Window *win);
        virtual void onCrashedWorker(Berkelium::Window* win);
        virtual void onCrashedPlugin(Berkelium::Window* win, Berkelium::WideString pluginName);
        virtual void onProvisionalLoadError(Berkelium::Window* win, Berkelium::URLString url, int errorCode, bool isMainFrame);
        virtual void onConsoleMessage(Berkelium::Window* win, Berkelium::WideString message, Berkelium::WideString sourceID, int line_no);
        virtual void onScriptAlert(Berkelium::Window* win, Berkelium::WideString message, Berkelium::WideString defaultValue, Berkelium::URLString url, int flags, bool &success, Berkelium::WideString &value);
        virtual void onNavigationRequested(Berkelium::Window* win, Berkelium::URLString newURL, Berkelium::URLString referrer, bool isNewWindow, bool &cancelDefaultAction);
        virtual void onLoadingStateChanged(Berkelium::Window* win, bool isLoading);
        virtual void onTitleChanged(Berkelium::Window* win, Berkelium::WideString title);
        virtual void onTooltipCHanged(Berkelium::Window* win, Berkelium::WideString text);
        virtual void onCrashed(Berkelium::Window* win);
        virtual void onUnresponsive(Berkelium::Window* win);
        virtual void onCreatedWindow(Berkelium::Window* win, Berkelium::Window* newWin, const Berkelium::Rect &initialRect);
        virtual void onWidgetCreated(Berkelium::Window* win, Berkelium::Widget* widget, int zIndex);
        virtual void onWidgetResize(Berkelium::Window* win, Berkelium::Widget* widget, int w, int h);
        virtual void onWidgetMove(Berkelium::Window* win, Berkelium::Widget* widget, int x, int y);
        virtual void onShowContextMenu(Berkelium::Window* win, const Berkelium::ContextMenuEventArgs& args);
        virtual void onJavascriptCallback(Berkelium::Window* win, void* replyMsg, Berkelium::URLString url, Berkelium::WideString funcName, Berkelium::Script::Variant *args, size_t numArgs);
        void registerCallback(CallbackHandler* handler);
        virtual void onRunFileChooser(Berkelium::Window* win, int mode, Berkelium::WideString title, Berkelium::FileString defaultFile);
        virtual void onExternalHost(Berkelium::Window* win, Berkelium::WideString message, Berkelium::URLString origin, Berkelium::URLString target);

    private:
        Berkelium::Window* bk_window;
        unsigned int width, height;
        GLuint texture_id;
        bool needs_full_refresh;
        bool verbose;
        char* scroll_buffer;
        std::vector<CallbackHandler*> handlers;
};

}
