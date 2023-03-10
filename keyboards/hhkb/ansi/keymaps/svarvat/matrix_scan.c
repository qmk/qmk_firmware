
uint16_t scrollDelayTimer;

void matrix_scan_user(void) {
    if (isMouseX4Started) {
        if (mouseRight) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.x = 12;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } else if (mouseLeft) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.x = -12;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } if (mouseDown) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.y = 12;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } else if (mouseUp) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.y = -12;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        }
    }
    else if (isMouseX2Started) {
        if (mouseDown) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.y = 4;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } else if (mouseUp) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.y = -4;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } if (mouseRight) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.x = 4;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } else if (mouseLeft) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.x = -4;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        }
    }
    else if (isMouseX1Started) {
        if (mouseDown) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.y = 1;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } else if (mouseUp) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.y = -1;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } if (mouseRight) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.x = 1;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        } else if (mouseLeft) {
            report_mouse_t currentReport = pointing_device_get_report();
            currentReport.x = -1;
            pointing_device_set_report(currentReport);
            pointing_device_send();
        }
    }
    if (isScrollX4Started) {
        if (scrollDown || scrollUp) {
            if (timer_elapsed(scrollDelayTimer) > 100) {
                report_mouse_t currentReport = pointing_device_get_report();
                currentReport.v = scrollUp ? 10 : -10;
                pointing_device_set_report(currentReport);
                pointing_device_send();
                scrollDelayTimer = timer_read();
            }
        } if (scrollLeft || scrollRight) {
            if (timer_elapsed(scrollDelayTimer) > 100) {
                report_mouse_t currentReport = pointing_device_get_report();
                currentReport.h = scrollLeft ? -10 : 10;
                pointing_device_set_report(currentReport);
                pointing_device_send();
                scrollDelayTimer = timer_read();
            }
        }
    }
    else if (isScrollX2Started) {
        if (scrollDown || scrollUp) {
            if (timer_elapsed(scrollDelayTimer) > 100) {
                report_mouse_t currentReport = pointing_device_get_report();
                currentReport.v = scrollUp ? 2 : -2;
                pointing_device_set_report(currentReport);
                pointing_device_send();
                scrollDelayTimer = timer_read();
            }
        } if (scrollLeft || scrollRight) {
            if (timer_elapsed(scrollDelayTimer) > 100) {
                report_mouse_t currentReport = pointing_device_get_report();
                currentReport.h = scrollLeft ? -2 : 2;
                pointing_device_set_report(currentReport);
                pointing_device_send();
                scrollDelayTimer = timer_read();
            }
        }
    }
    else if (isScrollX1Started) {
            if (scrollDown || scrollUp) {
                if (timer_elapsed(scrollDelayTimer) > 40) {
                    report_mouse_t currentReport = pointing_device_get_report();
                    currentReport.v = scrollUp ? 1 : -1;
                    pointing_device_set_report(currentReport);
                    pointing_device_send();
                    scrollDelayTimer = timer_read();
                }
            } if (scrollLeft || scrollRight) {
                if (timer_elapsed(scrollDelayTimer) > 40) {
                    report_mouse_t currentReport = pointing_device_get_report();
                    currentReport.h = scrollLeft ? -1 : 1;
                    pointing_device_set_report(currentReport);
                    pointing_device_send();
                    scrollDelayTimer = timer_read();
                }
            }
        }
}


