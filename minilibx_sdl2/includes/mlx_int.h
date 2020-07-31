/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:45:13 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 17:45:13 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_H
# define MLX_INT_H

# include "SDL.h"
# include "linked_lists.h"
# include <stdint.h>
# include <stdlib.h>

/***************************************************************** 
 * EVENT DEFINITIONS 
 *****************************************************************/
/* Input Event Masks. Used as event-mask window attribute and as arguments
   to Grab requests.  Not to be confused with event names.  */
#define NoEventMask			0L
#define KeyPressMask			(1L<<0)  
#define KeyReleaseMask			(1L<<1)  
#define ButtonPressMask			(1L<<2)  
#define ButtonReleaseMask		(1L<<3)  
#define EnterWindowMask			(1L<<4)  
#define LeaveWindowMask			(1L<<5)  
#define PointerMotionMask		(1L<<6)  
#define PointerMotionHintMask		(1L<<7)  
#define Button1MotionMask		(1L<<8)  
#define Button2MotionMask		(1L<<9)  
#define Button3MotionMask		(1L<<10) 
#define Button4MotionMask		(1L<<11) 
#define Button5MotionMask		(1L<<12) 
#define ButtonMotionMask		(1L<<13) 
#define KeymapStateMask			(1L<<14)
#define ExposureMask			(1L<<15) 
#define VisibilityChangeMask		(1L<<16) 
#define StructureNotifyMask		(1L<<17) 
#define ResizeRedirectMask		(1L<<18) 
#define SubstructureNotifyMask		(1L<<19) 
#define SubstructureRedirectMask	(1L<<20) 
#define FocusChangeMask			(1L<<21) 
#define PropertyChangeMask		(1L<<22) 
#define ColormapChangeMask		(1L<<23) 
#define OwnerGrabButtonMask		(1L<<24) 
/* Event names.  Used in "type" field in XEvent structures.  Not to be
confused with event masks above.  They start from 2 because 0 and 1
are reserved in the protocol for errors and replies. */
#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease		5
#define MotionNotify		6
#define EnterNotify		7
#define LeaveNotify		8
#define FocusIn			9
#define FocusOut		10
#define KeymapNotify		11
#define Expose			12
#define GraphicsExpose		13
#define NoExpose		14
#define VisibilityNotify	15
#define CreateNotify		16
#define DestroyNotify		17
#define UnmapNotify		18
#define MapNotify		19
#define MapRequest		20
#define ReparentNotify		21
#define ConfigureNotify		22
#define ConfigureRequest	23
#define GravityNotify		24
#define ResizeRequest		25
#define CirculateNotify		26
#define CirculateRequest	27
#define PropertyNotify		28
#define SelectionClear		29
#define SelectionRequest	30
#define SelectionNotify		31
#define ColormapNotify		32
#define ClientMessage		33
#define MappingNotify		34
#define GenericEvent		35
#define LASTEvent		36	/* must be bigger than any event # */
/* Key masks. Used as modifiers to GrabButton and GrabKey, results of QueryPointer,
   state in various key-, mouse-, and button-related events. */
#define ShiftMask		(1<<0)
#define LockMask		(1<<1)
#define ControlMask		(1<<2)
#define Mod1Mask		(1<<3)
#define Mod2Mask		(1<<4)
#define Mod3Mask		(1<<5)
#define Mod4Mask		(1<<6)
#define Mod5Mask		(1<<7)
/* modifier names.  Used to build a SetModifierMapping request or
   to read a GetModifierMapping request.  These correspond to the
   masks defined above. */
#define ShiftMapIndex		0
#define LockMapIndex		1
#define ControlMapIndex		2
#define Mod1MapIndex		3
#define Mod2MapIndex		4
#define Mod3MapIndex		5
#define Mod4MapIndex		6
#define Mod5MapIndex		7
/* button masks.  Used in same manner as Key masks above. Not to be confused
   with button names below. */
#define Button1Mask		(1<<8)
#define Button2Mask		(1<<9)
#define Button3Mask		(1<<10)
#define Button4Mask		(1<<11)
#define Button5Mask		(1<<12)

# define MLX_MAX_EVENT LASTEvent

typedef struct	s_mlx_event
{
	int		mask;
	void	*param;
	int		(*hook)();
}				t_mlx_event;

typedef struct	s_sdl_var
{
	t_mlx_event	hooks[MLX_MAX_EVENT];
	t_list		*win_list;
}				t_sdl_var;

typedef struct	s_mlx_img
{
	uint32_t		*array;
	int				bits_per_pixel;
	int				width;
	int				height;
}					t_mlx_img;

typedef struct		s_sdl_win
{
	t_sdl_var		*mlx_ptr;
	SDL_Window		*win_ptr;
	t_mlx_img		*img;
	SDL_Renderer	*renderer;
	SDL_Texture		*text;
	int				width;
	int				height;
}					t_sdl_win;

void	*mlx_init(void);
void	*mlx_new_image(t_sdl_var *mlx_ptr, int width, int height);
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
char	*mlx_get_data_addr(t_mlx_img *img_ptr, int *bits_per_pixel,
							int *size_line, int *endian);
void	my_mlx_pixel_put(t_mlx_img *data, int x, int y, int color);
void	draw_text(t_mlx_img *text, t_mlx_img *img, int x0, int y0);
int		mlx_put_image_to_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr, t_mlx_img *img_ptr,
								int x, int y);
int		mlx_destroy_image(t_sdl_var *mlx_ptr, t_mlx_img *img_ptr);
int		mlx_destroy_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr);

#endif