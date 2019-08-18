#include "idletimer.h"

#warning FIXME: Need to check for QX11Info below
#ifdef USE_XCB_SCREENSAVER
#include <xcb/xcb.h>
#include <QX11Info>
#include <xcb/screensaver.h>
#include <limits.h>

int IdleTimer::getIdleTime(){
    xcb_connection_t* conn = QX11Info::connection();
    int display = QX11Info::appScreen();

    xcb_screensaver_query_info_cookie_t replyCookie = xcb_screensaver_query_info(conn, QX11Info::appRootWindow(display));
    xcb_screensaver_query_info_reply_t* replyInfo = xcb_screensaver_query_info_reply(conn, replyCookie, NULL);

    uint32_t userIdle = replyInfo->ms_since_user_input;
    delete replyInfo;

    // Clamp the value
    if(userIdle > INT_MAX)
        userIdle = INT_MAX;

    return (int)userIdle;
}

#else

uint32_t IdleTimer::getIdleTime(){
    return 0;
}
#endif
