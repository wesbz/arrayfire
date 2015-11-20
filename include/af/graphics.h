/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#include <af/defines.h>
#include <af/array.h>

typedef unsigned long long af_window;

typedef struct {
    int row;
    int col;
    const char* title;
    af_colormap cmap;
} af_cell;

#ifdef __cplusplus
namespace af
{

/**
   \class Window

   \brief Window object to render af::arrays

   \ingroup graphics_func
 */
class AFAPI Window {
    private:
        af_window wnd;
        /* below attributes are used to track which
         * cell in the grid is being rendered currently */
        int _r;
        int _c;
        ColorMap _cmap;

        void initWindow(const int width, const int height, const char* const title);

    public:
        /**
           Creates a window object with default width
           and height with title set to "ArrayFire"

           \ingroup gfx_func_window
         */
        Window();

        /**
           Creates a window object with default width
           and height using the title provided by the user

           \param[in] title is the window title

           \ingroup gfx_func_window
         */
        Window(const char* const title);

        /**
           Creates a window object using the parameters
           provided by the user

           \param[in] width is the window width
           \param[in] height is the window height
           \param[in] title is the window title with default value as "ArrayFire"

           \ingroup gfx_func_window
         */
        Window(const int width, const int height, const char* const title="ArrayFire");

        /**
           Creates a window object with default width
           and height with title set to "ArrayFire"

           \param[in] wnd is an \ref af_window handle which can be retrieved by
           doing a get call on any \ref Window object

           \ingroup gfx_func_window
         */
        Window(const af_window wnd);
        /**
           Destroys the window handle

           \ingroup gfx_func_window
         */
        ~Window();

        // FIXME handle copying properly

        /**
           \return Returns the \ref af_window window handle.

           \ingroup gfx_func_window
         */
        af_window get() const { return wnd; }

        /**
           Set the start position where the window will appear

           \param[in] x is horizontal coordinate
           \param[in] y is vertical coordinate

           \ingroup gfx_func_window
         */
        void setPos(const unsigned x, const unsigned y);

        /**
           Set the window title

           \param[in] title is the window title

           \ingroup gfx_func_window
         */
        void setTitle(const char* const title);

#if AF_API_VERSION >= 31
        /**
           Set the window size

           \param[in]   w is target width of the window
           \param[in]   h is target height of the window

           \ingroup gfx_func_window
         */
        void setSize(const unsigned w, const unsigned h);
#endif

        /**
           Set the colormap to be used for subsequent rendering calls

           \param[in] cmap should be one of the enum values from \ref ColorMap

           \ingroup gfx_func_window
         */
        void setColorMap(const ColorMap cmap);

        /**
           Renders the input array as an image to the window

           \param[in] in is an \ref array
           \param[in] title parameter is used when this function is called in grid mode

           \note \p in should be 2d array or 3d array with 3 channels.

           \ingroup gfx_func_draw
         */
        void image(const array& in, const char* title=NULL);

#if AF_API_VERSION >= 32
        /**
           Renders the input array as an 3d line plot to the window

           \param[in] in is an \ref array
           \param[in] title parameter is used when this function is called in grid mode

           \note \p in should be 1d array of size 3n or 2d array with (3 x n) or (n x 3) channels.

           \ingroup gfx_func_draw
         */
        void plot3(const array& in, const char* title=NULL);
#endif

        /**
           Renders the input arrays as a 2D plot to the window

           \param[in] X is an \ref array with the x-axis data points
           \param[in] Y is an \ref array with the y-axis data points
           \param[in] title parameter is used when this function is called in grid mode

           \note \p X and \p Y should be vectors.

           \ingroup gfx_func_draw
         */

        void plot(const array& X, const array& Y, const char* const title=NULL);

        /**
           Renders the input arrays as a 2D scatter-plot to the window

           \param[in] X is an \ref array with the x-axis data points
           \param[in] Y is an \ref array with the y-axis data points
           \param[in] marker is an \ref markerType enum specifying which marker to use in the scatter plot
           \param[in] title parameter is used when this function is called in grid mode

           \note \p X and \p Y should be vectors.

           \ingroup gfx_func_draw
         */

        void scatter(const array& X, const array& Y, const af::markerType marker=AF_MARKER_POINT, const char* const title=NULL);
        /**
           Renders the input array as a histogram to the window

           \param[in] X is the data frequency \ref array
           \param[in] minval is the value of the minimum data point of the array whose histogram(\p X) is going to be rendered.
           \param[in] maxval is the value of the maximum data point of the array whose histogram(\p X) is going to be rendered.
           \param[in] title parameter is used when this function is called in grid mode

           \note \p X should be a vector.

           \ingroup gfx_func_draw
         */
        void hist(const array& X, const double minval, const double maxval, const char* const title=NULL);

#if AF_API_VERSION >= 32
        /**
           Renders the input arrays as a 3D surface plot to the window

           \param[in] S is an \ref array with the z-axis data points
           \param[in] title parameter is used when this function is called in grid mode

           \note \p S should be a 2D array

           \ingroup gfx_func_draw
         */
        void surface(const array& S, const char* const title);
#endif

#if AF_API_VERSION >= 32
        /**
           Renders the input arrays as a 3D surface plot to the window

           \param[in] xVals is an \ref array with the x-axis data points
           \param[in] yVals is an \ref array with the y-axis data points
           \param[in] S is an \ref array with the z-axis data points
           \param[in] title parameter is used when this function is called in grid mode

           \note \p X and \p Y should be vectors or 2D arrays \p S should be s 2D array

           \ingroup gfx_func_draw
         */
        void surface(const array& xVals, const array& yVals, const array& S, const char* const title);
#endif

        /**
           Setup grid layout for multiview mode in a window

           \param[in]   rows is number of rows you want to show in a window
           \param[in]   cols is number of coloumns you want to show in a window

           \ingroup gfx_func_window
        */
        void grid(const int rows, const int cols);

        /**
           This function swaps the background buffer to current view
           and polls for any key strokes while the window was in focus

           \ingroup gfx_func_window
        */
        void show();

        /**
           Check if window is marked for close. This usually
           happens when user presses ESC key while the window is in focus.

           \return     \ref AF_SUCCESS if window show is successful, otherwise an appropriate error code
           is returned.

           \ingroup gfx_func_window
        */
        bool close();

        /**
           This function is used to keep track of which cell in the grid mode is
           being currently rendered. When a user does Window(0,0), we internally
           store the cell coordinates and return a reference to the very object that
           called upon this function. This reference can be used later to issue
           draw calls using rendering functions.

           \return a reference to the object pointed by this
           to enable cascading this call with rendering functions.

           \ingroup gfx_window_func
         */
        inline Window& operator()(const int r, const int c) {
            _r = r; _c = c;
            return *this;
        }
};

}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
   C Interface wrapper for creating a window

   \param[out]  out is the handle to the created window
   \param[in]   width is the width of the window that will be created
   \param[in]   height is the height of the window that will be created
   \param[in]   title is the window title

   \return     \ref AF_SUCCESS if window creation is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_create_window(af_window *out, const int width, const int height, const char* const title);

/**
   C Interface wrapper for setting the start position when window is displayed

   \param[in]   wind is the window handle
   \param[in]   x is horizontal start coordinate
   \param[in]   y is vertical start coordinate

   \return     \ref AF_SUCCESS if set position for window is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_set_position(const af_window wind, const unsigned x, const unsigned y);

/**
   C Interface wrapper for setting window title

   \param[in]   wind is the window handle
   \param[in]   title is title of the window

   \return     \ref AF_SUCCESS if set title for window is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_set_title(const af_window wind, const char* const title);

#if AF_API_VERSION >= 31
/**
   C Interface wrapper for setting window position

   \param[in]   wind is the window handle
   \param[in]   w is target width of the window
   \param[in]   h is target height of the window

   \return     \ref AF_SUCCESS if set size for window is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_set_size(const af_window wind, const unsigned w, const unsigned h);
#endif

/**
   C Interface wrapper for drawing an array as an image

   \param[in]   wind is the window handle
   \param[in]   in is an \ref af_array
   \param[in]   props is structure \ref af_cell that has the properties that are used
   for the current rendering.

   \return     \ref AF_SUCCESS if rendering is successful, otherwise an appropriate error code
   is returned.

   \note \p in should be 2d array or 3d array with 3 channels.

   \ingroup gfx_func_draw
*/
AFAPI af_err af_draw_image(const af_window wind, const af_array in, const af_cell* const props);

/**
   C Interface wrapper for drawing an array as a plot

   \param[in]   wind is the window handle
   \param[in]   X is an \ref af_array with the x-axis data points
   \param[in]   Y is an \ref af_array with the y-axis data points
   \param[in]   props is structure \ref af_cell that has the properties that are used
   for the current rendering.

   \return     \ref AF_SUCCESS if rendering is successful, otherwise an appropriate error code
   is returned.

   \note \p X and \p Y should be vectors.

   \ingroup gfx_func_draw
*/
AFAPI af_err af_draw_plot(const af_window wind, const af_array X, const af_array Y, const af_cell* const props);

#if AF_API_VERSION >= 32
/**
   C Interface wrapper for drawing an array as a plot

   \param[in]   wind is the window handle
   \param[in]   X is an \ref af_array with the x-axis data points
   \param[in]   Y is an \ref af_array with the y-axis data points
   \param[in]   props is structure \ref af_cell that has the properties that are used
   \param[in] marker is an \ref markerType enum specifying which marker to use in the scatter plot
   for the current rendering.

   \return     \ref AF_SUCCESS if rendering is successful, otherwise an appropriate error code
   is returned.

   \note \p X and \p Y should be vectors.

   \ingroup gfx_func_draw
*/
AFAPI af_err af_draw_scatter(const af_window wind, const af_array X, const af_array Y, const af_cell* const props, const af_marker_type marker);
#endif

#if AF_API_VERSION >= 32
/**
   C Interface wrapper for drawing an array as a plot

   \param[in]   wind is the window handle
   \param[in]   P is an \ref af_array or matrix with the xyz-values of the points
   \param[in]   props is structure \ref af_cell that has the properties that are used
   for the current rendering.

   \return     \ref AF_SUCCESS if rendering is successful, otherwise an appropriate error code
   is returned.

   \note \p P should be a 3n x 1  vector or one of a 3xn or nx3 matrices.

   \ingroup gfx_func_draw
*/
AFAPI af_err af_draw_plot3(const af_window wind, const af_array P, const af_cell* const props);
#endif

/**
   C Interface wrapper for drawing an array as a histogram

   \param[in]   wind is the window handle
   \param[in]   X is the data frequency \ref af_array
   \param[in]   minval is the value of the minimum data point of the array whose histogram(\p X) is going to be rendered.
   \param[in]   maxval is the value of the maximum data point of the array whose histogram(\p X) is going to be rendered.
   \param[in]   props is structure \ref af_cell that has the properties that are used
   for the current rendering.

   \return     \ref AF_SUCCESS if rendering is successful, otherwise an appropriate error code
   is returned.

   \note \p X should be a vector.

   \ingroup gfx_func_draw
*/
AFAPI af_err af_draw_hist(const af_window wind, const af_array X, const double minval, const double maxval, const af_cell* const props);

#if AF_API_VERSION >= 32
/**
   C Interface wrapper for drawing arrayis as a surface

   \param[in]   wind is the window handle
   \param[in]   xVals is an \ref af_array with the x-axis data points
   \param[in]   yVals is an \ref af_array with the y-axis data points
   \param[in]   S is an \ref af_array with the z-axis data points
   \param[in]   props is structure \ref af_cell that has the properties that are used
   for the current rendering.

   \return     \ref AF_SUCCESS if rendering is successful, otherwise an appropriate error code
   is returned.

   \note \p X and \p Y should be vectors. \p S should be a 2D array

   \ingroup gfx_func_draw
*/
af_err af_draw_surface(const af_window wind, const af_array xVals, const af_array yVals, const af_array S, const af_cell* const props);
#endif

/**
   C Interface wrapper for grid setup in a window

   \param[in]   wind is the window handle
   \param[in]   rows is number of rows you want to show in a window
   \param[in]   cols is number of coloumns you want to show in a window

   \return     \ref AF_SUCCESS if grid setup for window is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_grid(const af_window wind, const int rows, const int cols);

/**
   C Interface wrapper for showing a window

   \param[in] wind is the window handle

   \return \ref AF_SUCCESS if window show is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_show(const af_window wind);

/**
   C Interface wrapper for checking if window is marked for close

   \param[out]  out is a boolean which indicates whether window is marked for close. This usually
                happens when user presses ESC key while the window is in focus.
   \param[in]   wind is the window handle

   \return     \ref AF_SUCCESS if \p wind show is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_is_window_closed(bool *out, const af_window wind);

/**
   C Interface wrapper for destroying a window handle

   \param[in]   wind is the window handle

   \return     \ref AF_SUCCESS if window destroy is successful, otherwise an appropriate error code
   is returned.

   \ingroup gfx_func_window
*/
AFAPI af_err af_destroy_window(const af_window wind);

#ifdef __cplusplus
}

#endif
