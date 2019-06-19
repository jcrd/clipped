/* This project is licensed under the MIT License (see LICENSE). */

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef VERSION
#define VERSION ""
#endif /* VERSION */

static void
print_usage(int code)
{
    fputs("usage: clipped [options]\n"
            "\n"
            "options:\n"
            "  -h            Show help message\n"
            "  -s SELECTION  Monitor this selection\n"
            "  -v            Show version\n",
            code ? stderr : stdout);

    exit(code);
}

int
main(int argc, char *argv[])
{
    const char *selection = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "hs:v")) != -1) {
        switch (opt) {
            case 'h':
                print_usage(EXIT_SUCCESS);
                break;
            case 's':
                selection = optarg;
                break;
            case 'v':
                printf("%s\n", VERSION);
                return EXIT_SUCCESS;
            default:
                print_usage(2);
        }
    }

    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Failed to open X display\n");
        return EXIT_FAILURE;
    }

    Window root = DefaultRootWindow(dpy);
    Atom clipboard = XInternAtom(dpy, "CLIPBOARD", False);

    if (!selection || strcmp(selection, "primary") == 0)
        XFixesSelectSelectionInput(dpy, root, XA_PRIMARY,
                XFixesSetSelectionOwnerNotifyMask);
    if (!selection || strcmp(selection, "clipboard") == 0)
        XFixesSelectSelectionInput(dpy, root, clipboard,
                XFixesSetSelectionOwnerNotifyMask);

    XEvent ev;
    while (!XNextEvent(dpy, &ev)) {
        XFixesSelectionNotifyEvent *e;
        e = (XFixesSelectionNotifyEvent *)&ev.xgeneric;
        if (e->selection == XA_PRIMARY)
            printf("PRIMARY\n");
        else if (e->selection == clipboard)
            printf("CLIPBOARD\n");
        fflush(stdout);
    }
}
