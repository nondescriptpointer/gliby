#include "TextureWindow.h"
#include <iostream>
#include <string.h>

using namespace gliby;

TextureWindow::TextureWindow(unsigned int w, unsigned int h, bool transp, bool verb):
    width(w),height(h),needs_full_refresh(true),verbose(verb){

    // generate a texture
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    GLfloat largest;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // generate scroll buffer
    scroll_buffer = new char[width*(height+1)*4];

    // create window
    Berkelium::Context *context = Berkelium::Context::create();
    bk_window = Berkelium::Window::create(context);
    delete context;
    bk_window->setDelegate(this);
    bk_window->resize(width, height);
    bk_window->setTransparent(transp);
}
TextureWindow::~TextureWindow(void){
    delete scroll_buffer;
    delete bk_window;
    glDeleteTextures(1, &texture_id); // will cause problems if texture is still being used
}

Berkelium::Window* TextureWindow::window(void) const {
    return bk_window;
}
GLuint TextureWindow::texture(void) const{
    return texture_id;
}

void TextureWindow::clear(void){
    unsigned char black = 0;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 1, 1, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, &black);
    needs_full_refresh = true;
}

void TextureWindow::onPaint(Berkelium::Window* win, const unsigned char* bitmap_in, const Berkelium::Rect &bitmap_rect,
    size_t num_copy_rects, const Berkelium::Rect* copy_rects, int dx, int dy, const Berkelium::Rect &scroll_rect){
    
    const int bytesPerPixel = 4;

    if(verbose){
        std::cout << (void*)win << " bitmap rect: w=" << bitmap_rect.width() << ", h=" << bitmap_rect.height() << ", (" << bitmap_rect.top() << "," << bitmap_rect.left() << ") tex size " << width << "x" << height << std::endl;
        //std::cout << "bmp: " << &bitmap_in << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    // if full refresh is needed, wait for a full update
    if(needs_full_refresh){
        if(bitmap_rect.left() != 0 || bitmap_rect.top() != 0 || (unsigned)bitmap_rect.right() != width || (unsigned)bitmap_rect.bottom() != height){
            return;
        }
        // full update received and needed, draw to texture
        if(verbose) std::cout << "Doing full paint" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap_in);
        needs_full_refresh = false;
        return;
    }

    // first, handle scrolling because we need to shift existing data
    if(dx != 0 || dy != 0){
        // scroll_rect contains the rect we need to move, so figure out where data is moved by translating it
        Berkelium::Rect scrolled_rect = scroll_rect.translate(-dx, -dy);
        // next figure out where they intersec to find scrolled region
        Berkelium::Rect scrolled_shared_rect = scroll_rect.intersect(scrolled_rect);
        // only do scrolling with non-zero intersection
        if(scrolled_shared_rect.width() > 0 && scrolled_shared_rect.height() > 0){
            // scroll is performed by moving shared_rect
            Berkelium::Rect shared_rect = scrolled_shared_rect.translate(dx, dy);

            int wid = scrolled_shared_rect.width();
            int hig = scrolled_shared_rect.height();
            if(verbose)
                std::cout << "Scroll rect: w=" << wid << ", h=" << hig << ", (" << scrolled_shared_rect.left() << "," << scrolled_shared_rect.top() << ") by (" << dx << "," << dy << ")" << std::endl;
            int inc = 1;
            char *outputBuffer = scroll_buffer;
            // source data is offset by 1 line to prevent memcpy aliasing (can happen if dy == 0 and dx != 0)
            char *inputBuffer = scroll_buffer+(width*1*bytesPerPixel);
            int jj = 0;
            if(dy > 0){
                // shift the buffer around so that we start in the extra row at the end and copy in reverse so that we don't cobber source data
                outputBuffer = scroll_buffer+((scrolled_shared_rect.top()+hig+1)*width-hig*wid)*bytesPerPixel;
                inputBuffer = scroll_buffer;
                inc = -1;
                jj = hig-1;
            }
            // copy data out of texture
            glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, inputBuffer);
            // manually copy out the region to the beginning of the buffer
            for(; jj < hig && jj >= 0; jj+=inc){
                memcpy(outputBuffer+(jj*wid)*bytesPerPixel,
                    inputBuffer+((scrolled_shared_rect.top()+jj)*width+scrolled_shared_rect.left())*bytesPerPixel,
                    wid*bytesPerPixel);
            }
            // push it back into the texture in the right location
            glTexSubImage2D(GL_TEXTURE_2D, 0, shared_rect.left(), shared_rect.top(), shared_rect.width(), shared_rect.height(), GL_BGRA, GL_UNSIGNED_BYTE, outputBuffer);
        }
    }
    
    if(verbose) std::cout << "Doing partial paint" << std::endl;

    // painting rects
    for(size_t i = 0; i < num_copy_rects; i++){
        int wid = copy_rects[i].width();
        int hig = copy_rects[i].height();
        int top = copy_rects[i].top() - bitmap_rect.top();
        int left = copy_rects[i].left() - bitmap_rect.left();
        for(int jj = 0; jj < hig; jj++){
            memcpy(scroll_buffer + jj*wid*bytesPerPixel,
                bitmap_in + (left + (jj + top) * bitmap_rect.width()) * bytesPerPixel,
                wid * bytesPerPixel
            );
        }
        glTexSubImage2D(GL_TEXTURE_2D, 0, copy_rects[i].left(), copy_rects[i].top(), wid, hig, GL_BGRA, GL_UNSIGNED_BYTE, scroll_buffer);
    }

    needs_full_refresh = false;
}


void TextureWindow::onAddressBarChanged(Berkelium::Window* win, Berkelium::URLString newURL){
    if(verbose) std::cout << "BK: Address bar URL changed to " << newURL << std::endl;
}
void TextureWindow::onStartLoading(Berkelium::Window* win, Berkelium::URLString newURL){
    if(verbose) std::cout << "BK: Starting loading of " << newURL << std::endl;
}
void TextureWindow::onLoad(Berkelium::Window* win){
    if(verbose) std::cout << "BK: Loading" << std::endl;
}
void TextureWindow::onCrashedWorker(Berkelium::Window* win){
    if(verbose) std::cerr << "BK: Worker crashed!" << std::endl;
}
void TextureWindow::onCrashedPlugin(Berkelium::Window* win, Berkelium::WideString pluginName){
    if(verbose) std::wcerr << "BK: Plugin crashed: " << pluginName << std::endl;
}
void TextureWindow::onProvisionalLoadError(Berkelium::Window* win, Berkelium::URLString url, int errorCode, bool isMainFrame){
    if(verbose){
        std::cerr << "BK: Provisional load error " << url << ": " << errorCode;
        if(isMainFrame) std::wcerr << " (main frame)";
        std::cerr << std::endl;
    }
}
void TextureWindow::onConsoleMessage(Berkelium::Window* win, Berkelium::WideString message, Berkelium::WideString sourceID, int line_no){
    if(verbose) std::wcout << "BK: Console message: " << message << " from " << sourceID << " line " << line_no << std::endl;
}
void TextureWindow::onScriptAlert(Berkelium::Window* win, Berkelium::WideString message, Berkelium::WideString defaultValue, Berkelium::URLString url, int flags, bool &success, Berkelium::WideString &value){
    if(verbose) std::wcout << "BK: Script alert: " << message << std::endl;
}
void TextureWindow::onNavigationRequested(Berkelium::Window* win, Berkelium::URLString newURL, Berkelium::URLString referrer, bool isNewWindow, bool &cancelDefaultAction){
    if(verbose) std::cout << "BK: Navigation requested " << newURL << " by " << referrer << (isNewWindow ? " (new window)" : " (same window)") << std::endl;
}
void TextureWindow::onLoadingStateChanged(Berkelium::Window* win, bool isLoading){
    if(verbose) std::cout << "BK: Loading state changed: " << (isLoading ? "loading" : "stopped") << std::endl;
}
void TextureWindow::onTitleChanged(Berkelium::Window* win, Berkelium::WideString title){
    if(verbose) std::wcout << "BK: Title changed to " << title << std::endl;
}
void TextureWindow::onTooltipCHanged(Berkelium::Window* win, Berkelium::WideString text){
    if(verbose) std::wcout << "BK: Tooltip changed to " << text << std::endl;
}
void TextureWindow::onCrashed(Berkelium::Window* win){
    if(verbose) std::cerr << "BK: Crashed!" << std::endl;
}
void TextureWindow::onUnresponsive(Berkelium::Window* win){
    if(verbose) std::cerr << "BK: Unresponsive" << std::endl;
}
void TextureWindow::onCreatedWindow(Berkelium::Window* win, Berkelium::Window* newWin, const Berkelium::Rect &initialRect){
    if(verbose) std::cout << "BK: Created window" << std::endl;
    if(initialRect.mWidth < 1 || initialRect.mHeight < 1){
        newWin->resize(width,height);
    }
    //newWin->setDelegate(this);
    newWin->destroy();
}
void TextureWindow::onWidgetCreated(Berkelium::Window* win, Berkelium::Widget* widget, int zIndex){
    if(verbose) std::cout << "BK: Widget created " << widget << " index " << zIndex << std::endl;
}
void TextureWindow::onWidgetResize(Berkelium::Window* win, Berkelium::Widget* widget, int w, int h){
    if(verbose) std::cout << "BK: Widget resize " << widget << " " << w << "x" << h << std::endl;
}
void TextureWindow::onWidgetMove(Berkelium::Window* win, Berkelium::Widget* widget, int x, int y){
    if(verbose) std::cout << "BK: Widget move " << widget << " " << x << "x" << y << std::endl;
}
void TextureWindow::onShowContextMenu(Berkelium::Window* win, const Berkelium::ContextMenuEventArgs& args){
    if(verbose){
        std::cout << "BK: Context menu at " << args.mouseX << "," << args.mouseY << " type: ";
        switch(args.mediaType){
            case Berkelium::ContextMenuEventArgs::MediaTypeImage:
                std::cout << "image";
                break;
            case Berkelium::ContextMenuEventArgs::MediaTypeVideo:
                std::cout << "video";
                break;
            case Berkelium::ContextMenuEventArgs::MediaTypeAudio:
                std::cout << "audio";
                break;
            default:
                std::cout << "other";
                break;
        }
        if(args.isEditable || args.editFlags){
            std::cout << " (";
            if(args.isEditable) std::cout << "editable; ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanUndo) std::cout << "Undo, ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanRedo) std::cout << "Redo, ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanCut) std::cout << "Cut, ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanCopy) std::cout << "Copy, ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanPaste) std::cout << "Paste, ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanDelete) std::cout << "Delete, ";
            if(args.editFlags & Berkelium::ContextMenuEventArgs::CanSelectAll) std::cout << "Select All, ";
        }
        std::cout << ")";
        std::cout << std::endl;
        if(args.linkUrl.length()) std::cout << "  Link URL: " << args.linkUrl << std::endl;
        if(args.srcUrl.length()) std::cout << "  Source URL: " << args.srcUrl << std::endl;
        if(args.pageUrl.length()) std::cout << "  Page URL: " << args.pageUrl << std::endl;
        if(args.frameUrl.length()) std::cout << "  Frame URL: " << args.frameUrl << std::endl;
        if(args.selectedText.length()) std::wcout << "  Selected Text: " << args.selectedText << std::endl;
    }
}

void TextureWindow::onJavascriptCallback(Berkelium::Window* win, void* replyMsg, Berkelium::URLString url, Berkelium::WideString funcName, Berkelium::Script::Variant *args, size_t numArgs){
    if(verbose){
        std::cout << "BK: Javascript callback at URL " << url << ", " << (replyMsg ? "synchronous" : "async") << std::endl;
        std::wcout << L"  Function name: " << funcName << std::endl;
        for(size_t i = 0; i < numArgs; i++){
            Berkelium::WideString jsonString = Berkelium::Script::toJSON(args[i]);
            std::wcout << "  Argument " << i << ": ";
            if(args[i].type() == Berkelium::Script::Variant::JSSTRING){
                std::wcout << "(string) " << args[i].toString() << std::endl;
            }else{
                std::wcout << jsonString << std::endl;
            }
            Berkelium::Script::toJSON_free(jsonString);
        }
        if(replyMsg){
            win->synchronousScriptReturn(replyMsg, numArgs ? args[0] : Berkelium::Script::Variant());
        }
    }
    for(std::vector<CallbackHandler*>::size_type e = 0; e < handlers.size(); e++){
        std::wcout << std::wstring(funcName.data(),funcName.length()) << std::endl;
        std::wcout << handlers[e]->funcName << std::endl;
        if(std::wstring(funcName.data(),funcName.length()) == std::wstring(handlers[e]->funcName.data(),handlers[e]->funcName.length())){
            handlers[e]->func();
        }
    }
}

void TextureWindow::registerCallback(CallbackHandler* handler){
    handlers.push_back(handler);
}

void TextureWindow::onRunFileChooser(Berkelium::Window* win, int mode, Berkelium::WideString title, Berkelium::FileString defaultFile){
    if(verbose){
        std::wcout << "BK: Run file chooser type " << mode << ", title " << title << ":" << std::endl;
        std::wcout << defaultFile << std::endl;
    }
    win->filesSelected(NULL);
}

void TextureWindow::onExternalHost(Berkelium::Window* win, Berkelium::WideString message, Berkelium::URLString origin, Berkelium::URLString target){
    if(verbose){
        std::cout << "BK: External host at URL from " << origin << " to " << target << ": " << message << std::endl;
    }
}
