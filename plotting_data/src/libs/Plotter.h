/* ----------------------------------------------------------------------------
*  Bibliotheque de plot basée sur libgd developpee dans le but de visualiser
* le dataset recensant les bornes Belib sur Paris.
*  
*  Author : Juba Hamma. 2023.
* ---------------------------------------------------------------------------- 
*/
#ifndef PLOTTER_H
#define PLOTTER_H

#include <stdlib.h>
#include <gd.h>

#define PI 3.141592

/* --------------------------------------------------------------------------- */
// Structures -> Check l'ordre des arguments pour la contiguite memoire
/* --------------------------------------------------------------------------- */

/**
 * @brief Structure definissant un certain style de plot
 * 
 */
typedef struct LineStyle_s {
    char style;     /**< Style de plot : '-' : line, ':' dashed,
                                          '' : point seulement */
    int  w;         /**< Epaisseur du trait*/
    char marker;    /**< Type de marker : 's' : carré, 'o' : cercle,
                                           '' : pas de marker */
    int  ms;        /**< Markersize*/
    int  color[3];  /**< Couleur rgb*/
} LineStyle;

/* --------------------------------------------------------------------------- */
/**
 * @brief Structure associant un vecteur de donnees labelisé à un LineStyle
 * 
 */
typedef struct LineData_s {
    size_t len_data;      /**< Taille du vecteur de data */
    int *x;               /**< Vecteur de data X */
    int *y;               /**< Vecteur de data Y */
    int max_X;            /**< Maximum des valeurs X */
    int max_Y;            /**< Maximum des valeurs Y */
    char* label;
    LineStyle *linestyle;  /**< LineStyle */
} LineData; 

/* --------------------------------------------------------------------------- */
/**
 * @brief Structure stockant un ensemble de LineData et de données relatives à la
 * création d'une figure
 * 
 */
typedef struct Figure_s {
    gdImage *img;        /**< Pointeur sur objet gdImage */
    size_t nb_linedata;  /**< Nombre de linedata dans la figure */
    LineData **linedata;  /**< Vecteur de LineData */
    int max_X;           /**< max de l'ensemble des max_X de linedata[] */
    int max_Y;           /**< max de l'ensemble des max_Y de linedata[] */
    int pad[2];          /**< Padding pour definir canvas (cvs) et orig */
    int orig[2];         /**< Coordonnees de l'origine des plots */    
    int margin[2];       /**< Marge droite et haut (evite de toucher les bords)*/    
    int color_bg[3];     /**< Couleur du fond de la figure */
    int color_cvs_bg[3]; /**< Couleur du fond du canvas */
    int color_axes[3];   /**< Couleur des axes*/
} Figure;


/* --------------------------------------------------------------------------- */
// Declaration fonctions
/* --------------------------------------------------------------------------- */

/**
 * @brief Transforme les degrés en radians.
 * 
 * @param angle Angle en degrés
 * @return float Angle en radians
 */
float Deg2rad(float angle);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param x_array 
 * @param n 
 * @return int 
 */
int Maxval_array(const int x_array[], size_t n);

/* --------------------------------------------------------------------------- */
/**
 * @brief Get the Couleur object
 * 
 * @param im_fig 
 * @param couleur 
 * @return int 
 */
int GetCouleur(gdImagePtr im_fig, const int couleur[3]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param dir_figures 
 * @param filename_fig 
 */
void Save_to_png(Figure *fig, const char *dir_figures, const char *filename_fig);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param couleur_bg 
 * @param couleur_canvas_bg 
 */
void Make_background(Figure *fig, const int couleur_bg[3],\
        const int couleur_canvas_bg[3]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param couleur 
 */
void Make_support_axes(Figure *fig, const int couleur[3]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param im_fig 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @param linestyle 
 */
void ImageLineEpaisseur(gdImagePtr im_fig, const int x1, const int y1, const int x2, \
            const int y2, LineStyle *linestyle);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param x1 
 * @param y1 
 * @param linestyle 
 */
void PlotPoint(Figure *fig, const int x1, const int y1,LineStyle *linestyle);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param linedata 
 */
void PlotLine(Figure *fig, LineData *linedata);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param len_pts 
 * @param pts 
 * @param pts_dessin 
 */
void Transform_dataX_to_plot(Figure *fig, size_t len_pts, const int pts[], \
            int* pts_dessin);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param len_pts 
 * @param pts 
 * @param pts_dessin 
 */
void Transform_dataY_to_plot(Figure *fig, size_t len_pts, const int pts[], \
            int* pts_dessin);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param len_pts 
 * @param pts 
 * @param direction 
 * @return int* 
 */
int *Transform_data_to_plot(Figure *fig, size_t len_pts, const int pts[], \
            char direction);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param linestyle 
 * @param style 
 * @param color 
 * @param width 
 * @param marker 
 * @param ms 
 */
void Init_linestyle(LineStyle *linestyle, char style,const int color[3], int width, \
            char marker, int ms);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param linedata 
 * @param len_data 
 * @param ptx 
 * @param pty 
 * @param label 
 * @param linestyle 
 */
void Init_linedata(LineData *linedata, int len_data, int ptx[], int pty[], \
            char* label, LineStyle *linestyle);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param color 
 */
void Change_fig_axes_color(Figure *fig, int color[3]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param color 
 */
void Change_fig_cvs_bg(Figure *fig, int color[3]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param color 
 */
void Change_fig_bg(Figure *fig, int color[3]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param figsize 
 * @param pad 
 * @param margin 
 */
void Init_figure(Figure *fig, int figsize[2], int pad[2], int margin[2]);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param linestyle 
 */
void Print_debug_ls(LineStyle *linestyle);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param linedata 
 */
void Print_debug_ld(LineData *linedata);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param x_array 
 * @param n 
 * @return int 
 */
int Maxval_array(const int x_array[], size_t n);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int Max_int(int x, int y);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int Min_int(int x, int y);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param xlabel 
 * @param font 
 * @param size 
 * @param color 
 * @param decalage_X 
 * @param decalage_Y 
 */
void Make_xlabel(Figure *fig, char* xlabel, char* font, int size, int color[3],\
             int decalage_X, int decalage_Y);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param ylabel 
 * @param font 
 * @param size 
 * @param color 
 * @param decalage_X 
 * @param decalage_Y 
 */
void Make_ylabel(Figure *fig, char* ylabel, char* font, int size, int color[3],\
             int decalage_X, int decalage_Y);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param font 
 * @param size 
 * @param decal_X 
 * @param decal_Y 
 * @param ecart 
 */
void Make_legend(Figure *fig, char* font, int size, int decal_X, int decal_Y, \
            int ecart);

/* --------------------------------------------------------------------------- */
/**
 * @brief 
 * 
 * @param fig 
 * @param font 
 * @param fontsize 
 */
void Make_yticks_ygrid(Figure *fig, char* font, int fontsize);


/* --------------------------------------------------------------------------- */
// Définition des fonctions
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
int Maxval_array(const int x_array[], size_t n)
{
    int t, i;
    t = x_array[0];
    for(i = 1; i < n; i++)
    {
        t = (x_array[i] > t) ? x_array[i] : t;
    }
    return t;
}

/* --------------------------------------------------------------------------- */
float Deg2rad(float angle)
{
    return angle*PI/180;
}

/* --------------------------------------------------------------------------- */
void Save_to_png(Figure *fig, const char *dir_figures, const char *filename_fig)
{
    FILE *pngout_fig;

    char path_outputFig[40] = {""};
    strcat(path_outputFig, dir_figures);
    strcat(path_outputFig, filename_fig);
    pngout_fig = fopen(path_outputFig, "wb");

    /* Output the image to the disk file in PNG format. */
    gdImagePng(fig->img, pngout_fig);

    /* Close the files. */
    fclose(pngout_fig);

    free(fig->linedata);

}


/* --------------------------------------------------------------------------- */
void Make_background(Figure *fig,\
                        const int color_bg[3], const int color_canvas_bg[3])
{
    /* Remplissage du fond */
    gdImageFilledRectangle(fig->img,\
                        0, 0,\
                        fig->img->sx-1, fig->img->sy-1,
                        GetCouleur(fig->img, color_bg));

    /* Remplissage du canvas */
    gdImageFilledRectangle(fig->img,\
                        fig->pad[0], fig->pad[1],\
                        fig->img->sx-1, fig->img->sy-1 - fig->pad[1],\
                        GetCouleur(fig->img, color_canvas_bg));
}

/* --------------------------------------------------------------------------- */
void ImageLineEpaisseur(gdImagePtr im_fig,\
    const int x1, const int y1, const int x2, const int y2, LineStyle *linestyle)
{
                    
    gdImageSetThickness(im_fig, linestyle->w);
    if (linestyle->style == '-') {
        gdImageLine(im_fig, x1, y1,   x2,   y2,\
                    GetCouleur(im_fig, linestyle->color));
    } else if (linestyle->style == ':') {
        gdImageDashedLine(im_fig, x1, y1,   x2,   y2,\
                   GetCouleur(im_fig, linestyle->color));
    } else {

    }
    
    gdImageSetThickness(im_fig, 1);
}


/* --------------------------------------------------------------------------- */
void Make_support_axes(Figure *fig, const int couleur[3])
{
    int w_axes = 3;
    LineStyle linestyle_axe;
    Init_linestyle(&linestyle_axe, '-', couleur, w_axes, ' ', 0);

    // axe vertical
    ImageLineEpaisseur(fig->img,\
                            fig->orig[0]-(w_axes-1), fig->orig[1]+(w_axes-1),\
                            fig->orig[0]-(w_axes-1), fig->pad[1],\
                            &linestyle_axe); 

    // axe horizontal
    ImageLineEpaisseur(fig->img,\
                            fig->orig[0]-(w_axes-1),    fig->orig[1]+(w_axes-1),\
                            fig->img->sx-1,  fig->orig[1]+(w_axes-1),
                            &linestyle_axe); 
}

/* --------------------------------------------------------------------------- */
void PlotPoint(Figure *fig, const int x1, const int y1,\
                        LineStyle *linestyle)
{
    if ( x1 != fig->orig[0] && y1 != fig->orig[1])
    {
        gdImageFilledEllipse(fig->img, x1, y1,\
            linestyle->ms, linestyle->ms, GetCouleur(fig->img, linestyle->color));
    } else if (x1 == fig->orig[0] && y1 != fig->orig[1])
    {   
        // Arc lorsque pt sur axe vertical
        gdImageFilledArc (fig->img, x1, y1, linestyle->ms, linestyle->ms,\
                          -90, 90,\
                          GetCouleur(fig->img, linestyle->color), gdArc);
    } else if (x1 != fig->orig[0] && y1 == fig->orig[1])
    {
        // Arc lorsque pt sur axe vertical
        gdImageFilledArc (fig->img, x1, y1, linestyle->ms, linestyle->ms,\
                          -180, 0,\
                          GetCouleur(fig->img, linestyle->color), gdArc);
    } else {

    }

}

/* --------------------------------------------------------------------------- */
void PlotLine(Figure *fig, LineData *linedata)
{
    int *x_plot = Transform_data_to_plot(fig, linedata->len_data, linedata->x, 'x');
    int *y_plot = Transform_data_to_plot(fig, linedata->len_data, linedata->y, 'y');   

    // Prise en compte du decalage de l'origine
    // printf("Orig = %d, %d \n", orig[0], orig[1]);
    for (int i=0; i < linedata->len_data-1; i++) 
    {
        ImageLineEpaisseur(fig->img,\
                x_plot[i]   + fig->orig[0],   y_plot[i] + fig->orig[1],\
                x_plot[i+1] + fig->orig[0], y_plot[i+1] + fig->orig[1],\
                linedata->linestyle);

        
        PlotPoint(fig,\
            x_plot[i] + fig->orig[0], y_plot[i] + fig->orig[1], linedata->linestyle);

        if (i == linedata->len_data-2) {
            PlotPoint(fig,\
                            x_plot[i+1] + fig->orig[0],\
                            y_plot[i+1] + fig->orig[1],\
                            linedata->linestyle);
        }
    }

    free(x_plot);
    free(y_plot);
}

/* --------------------------------------------------------------------------- */
void Transform_dataX_to_plot(Figure *fig, size_t len_pts,\
                                    const int pts[], int* pts_dessin)
{
    // Taile de la zone de dessin
    const int w_dessin = fig->img->sx - fig->orig[0] - fig->margin[0] - 1;

    for (int i = 0; i < len_pts; i++)
    {
        pts_dessin[i] = (pts[i] * w_dessin) / fig->max_X;
        // printf("Point : %d, %d \n", i, pts_dessin[i]);
    }

}


/* --------------------------------------------------------------------------- */
void Transform_dataY_to_plot(Figure *fig, size_t len_pts, \
                                    const int pts[], int* pts_dessin)
{
    // Taile de la zone de dessin

    const int h_dessin = fig->orig[1] - fig->pad[1] - fig->margin[1];   
    for (int i = 0; i < len_pts; i++)
    {
        pts_dessin[i] = -(pts[i] * h_dessin) / fig->max_Y;
        // printf("Point : %d, %d \n", i, pts_dessin[i]);
    }

}

/* --------------------------------------------------------------------------- */
int *Transform_data_to_plot(Figure *fig, size_t len_pts,\
                                  const int pts[], char direction)
{
    int *pts_dessin = malloc(len_pts * sizeof(int));

    if (pts_dessin == NULL) {
        printf("Erreur : Pas assez de memoire.\n");
        free(pts_dessin);
        exit(EXIT_FAILURE);
    }    

    // Taile de la zone de dessin
    if (direction == 'x') {
        Transform_dataX_to_plot(fig, len_pts, pts, pts_dessin);
    } else if (direction == 'y')
    {
        Transform_dataY_to_plot(fig, len_pts, pts, pts_dessin);
    }
    else 
    {
        printf("Erreur : Direction de tracé inconnue.\n");
        free(pts_dessin);
        exit(EXIT_FAILURE);
    }
    
    return pts_dessin;
}

/* --------------------------------------------------------------------------- */
int GetCouleur(gdImagePtr im_fig, const int couleur[3])
{
    return gdImageColorAllocate(im_fig, couleur[0], couleur[1], couleur[2]);
}

/* --------------------------------------------------------------------------- */
void Init_figure(Figure *fig, int figsize[2], int pad[2], int margin[2])
{

    /* Initialisation de tous les parametres*/

    fig->img = gdImageCreate(figsize[0],figsize[1]);
    fig->pad[0] = pad[0];
    fig->pad[1] = pad[1];
    fig->orig[0] = fig->pad[0];
    fig->orig[1] = fig->img->sy - fig->pad[1] -1;
    fig->margin[0] = margin[0];
    fig->margin[1] = margin[1];

    int col_fond[3]   = {37, 44, 56};     // bleu-gris
    int col_cvs[3] = {0, 0, 0}; 
    int col_axes[3] = {255, 255, 255}; 

    for (int i = 0; i < 3; i++)
    {
        fig->color_bg[i] = col_fond[i];
        fig->color_cvs_bg[i] = col_cvs[i];        
        fig->color_axes[i] = col_axes[i];
    }
    fig->nb_linedata = 0;
    fig->linedata = NULL;
    
    Make_background(fig, fig->color_bg, fig->color_cvs_bg);
    Make_support_axes(fig, fig->color_axes);

    fig->max_X = 0;
    fig->max_Y = 0;
}

/* --------------------------------------------------------------------------- */
void Change_fig_bg(Figure *fig, int color[3]) 
{
    for (int i = 0; i < 3; i++)
    {
        fig->color_bg[i] = color[i];
    }
    Make_background(fig, fig->color_bg, fig->color_cvs_bg);                                           
}

/* --------------------------------------------------------------------------- */
void Change_fig_cvs_bg(Figure *fig, int color[3]) 
{
    for (int i = 0; i < 3; i++)
    {
        fig->color_cvs_bg[i] = color[i];        
    }
    Make_background(fig, fig->color_bg, fig->color_cvs_bg);
}

/* --------------------------------------------------------------------------- */
void Change_fig_axes_color(Figure *fig, int color[3]) 
{
    for (int i = 0; i < 3; i++)
    {
        fig->color_axes[i] = color[i];
    }
    Make_support_axes(fig, fig->color_axes);
}

/* --------------------------------------------------------------------------- */
void Init_linedata(LineData *linedata, int len_data, int ptx[], int pty[],
                    char* label, LineStyle *linestyle)
{
    // int *ptx_plot = Transform_data_to_plot(fig, len_data, ptx, 'x');
    // int *pty_plot = Transform_data_to_plot(fig, len_data, pty, 'y');
    linedata->len_data = len_data;
    linedata->x = ptx;
    linedata->y = pty;
    linedata->max_X = Maxval_array(linedata->x, linedata->len_data);
    linedata->max_Y = Maxval_array(linedata->y, linedata->len_data);
    linedata->label = label;
    linedata->linestyle = linestyle;
}

/* --------------------------------------------------------------------------- */
void Init_linestyle(LineStyle *linestyle, char style,\
        const int color[3], int width, char marker, int ms)
{
    linestyle->style = style;
    for (int i = 0; i < 3; i++)
    {
        linestyle->color[i] = color[i];
    }    
    linestyle->w = width;
    linestyle->marker = marker;
    linestyle->ms = ms;
}

/* --------------------------------------------------------------------------- */
void Print_debug_ls(LineStyle *linestyle)
{
    printf("*** Debug linestyle\n");
    printf("* Style        = %c \n", linestyle->style);
    printf("* Width        = %d \n", linestyle->w);
    printf("* Marker       = %c \n", linestyle->marker);
    printf("* MarkerSize   = %d \n", linestyle->ms);
    printf("* Color        = %d,%d,%d \n", linestyle->color[0],\
                                           linestyle->color[1],\
                                           linestyle->color[2]);
    printf("*** End linestyle\n");
}

/* --------------------------------------------------------------------------- */
void Print_debug_ld(LineData *linedata)
{
    printf("*** Debug linedata\n");
    printf("* Label    = %s \n", linedata->label);
    printf("* Len data = %ld \n", linedata->len_data);
    printf("* Max X    = %d \n", linedata->max_X);
    printf("* Max Y    = %d \n", linedata->max_Y);
    Print_debug_ls(linedata->linestyle);
    printf("*** End linedata\n\n");
}

/* --------------------------------------------------------------------------- */
int Max_int(int x, int y) 
{
    return (x < y) ? y : x ;
}

/* --------------------------------------------------------------------------- */
int Min_int(int x, int y) 
{
    return (x > y) ? y : x ;
}

/* --------------------------------------------------------------------------- */
void Update_fig(Figure *fig, LineData *linedata)
{
    fig->nb_linedata++;
    fig->linedata = (LineData **)realloc(fig->linedata, fig->nb_linedata*sizeof(LineData));

    if (fig->linedata == NULL) {
        printf("Erreur : Pas assez de memoire.\n");
        free(fig->linedata);
        exit(EXIT_FAILURE);
    }

    // Index = nb line - 1
    fig->linedata[fig->nb_linedata-1] = linedata;

    // Print_debug_ld(fig->linedata[fig->nb_linedata]);

    fig->max_X = Max_int(fig->max_X, linedata->max_X);
    fig->max_Y = Max_int(fig->max_Y, linedata->max_Y);

}

/* --------------------------------------------------------------------------- */
void Make_xlabel(Figure *fig, char* xlabel, char* font, int size, int color[3],\
                    int decalage_X, int decalage_Y)
{
    // Pos avec decalage : Y decal autre sens
    // Prise en compte de la longueur du label
    int posX_xlabel = fig->orig[0] + (fig->img->sx - fig->pad[0])/2 - \
                              (strlen(xlabel) * size/3) + decalage_X;
    int posY_xlabel = fig->img->sy - (fig->pad[1]/10)                 - decalage_Y; 

    // int brect[8] = {0};
    gdImageStringFT(fig->img, NULL,\
                            GetCouleur(fig->img, color), font,\
                                size, 0., posX_xlabel, posY_xlabel, xlabel);    
    //Avoid memory leaks
    gdFontCacheShutdown();
    // printf("%s \n", errStringFT); 
}

/* --------------------------------------------------------------------------- */
void Make_ylabel(Figure *fig, char* ylabel, char* font, int size, int color[3],\
                     int decalage_X, int decalage_Y)
{
    // Pos avec decalage : Y decal autre sens
    int posX_ylabel = fig->pad[0]/2 - fig->pad[0]/4      + decalage_X;

    // Prise en compte de la longueur du label
    int posY_ylabel = (fig->orig[1] + (fig->pad[1]))/2 + \
                            (strlen(ylabel) * size/3)  + decalage_Y;   

    int brect[8] = {0};
    char *errStringFT = gdImageStringFT(fig->img, brect,\
                            GetCouleur(fig->img, color), font,\
                                size, Deg2rad(90.), posX_ylabel, posY_ylabel, ylabel);    

    printf("%s \n", errStringFT); 
    //Avoid memory leaks
    gdFontCacheShutdown();
}

/* --------------------------------------------------------------------------- */
void Make_legend(Figure *fig, char* font, int size,\
                    int decal_X, int decal_Y, int ecart)
{
    // Position des 8 legendes possibles
    int w_canvas = fig->img->sx - fig->pad[0];
    int pos_midcanvas = fig->orig[0] + w_canvas/2;

    int pos_X[8] = {fig->orig[0]+5  + decal_X, fig->orig[0]+5  + decal_X,\
                    fig->orig[0]+5  + decal_X, fig->orig[0]+5  + decal_X,\
                    pos_midcanvas + decal_X, pos_midcanvas + decal_X,\
                    pos_midcanvas + decal_X, pos_midcanvas + decal_X};

    int ecart_base = 6;
    int ecart_Y = ecart_base + ecart;
    int pos_Y[8] = {  (size + ecart_Y) - decal_Y,  2*(size + ecart_Y) - decal_Y,\
                    3*(size + ecart_Y) - decal_Y,  4*(size + ecart_Y) - decal_Y,\
                      (size + ecart_Y) - decal_Y,  2*(size + ecart_Y) - decal_Y,\
                    3*(size + ecart_Y) - decal_Y,  4*(size + ecart_Y) - decal_Y};

    // Longueur petit trait
    int long_trait_leg = 30;
    // Decalage apres trait
    int decalage_trait_leg = long_trait_leg + 10;

    // Print des petits traits de legende pour chaque plot

    for (int i = 0; i < fig->nb_linedata; i++)
    { 
        ImageLineEpaisseur(fig->img,\
                    pos_X[i]                   ,   pos_Y[i]-size/2,\
                    pos_X[i]+long_trait_leg,   pos_Y[i]-size/2,\
                    fig->linedata[i]->linestyle);
    }

    char *errStringFT;
    int brect[8] = {0};
    int white[3]  = {255, 255, 255};   //white

    for (int i = 0; i < fig->nb_linedata; i++)
    {
        errStringFT= gdImageStringFT(fig->img, brect,\
                            GetCouleur(fig->img, white), font,\
                                size, 0.,\
                                decalage_trait_leg+pos_X[i], pos_Y[i],\
                                fig->linedata[i]->label);        
    }

    if (errStringFT != NULL) {
        printf("%s\n", errStringFT);
    }

    //Avoid memory leaks
    gdFontCacheShutdown();
}


/* --------------------------------------------------------------------------- */
void Make_yticks_ygrid(Figure *fig, char* font, int fontsize)
{
    if (fig->max_Y == 0)
    {
        printf("Erreur : pas de ticks pour un max a 0.");
        exit(EXIT_FAILURE);
    }

    // int nb_ticks = Min_int(fig->max_Y, 10);
    // printf("Nb ticks  = %d \n", nb_ticks);

    // int itv = fig->max_Y / nb_ticks;
    // printf("Itv       = %d \n", itv);

    int itv=0, itv_minor=0;
    if (fig->max_Y <= 10) {
        itv = 1;
        itv_minor = 0;
    } else if (fig->max_Y <= 20)
    {
        itv = 2;
        itv_minor = 1;
    } else if (fig->max_Y <= 50)
    {
        itv = 5;
        itv_minor = 1;
    } else if (fig->max_Y <= 100)
    {
        itv = 10;
        itv_minor = 2;
    }
    
    printf("Itv       = %d \n", itv);
    printf("Itv minor = %d \n", itv_minor);
    int nb_ticks = fig->max_Y / itv;

    int nb_ticks_min = 0;    
    if (itv_minor != 0) {
        nb_ticks_min= (fig->max_Y / itv_minor) / nb_ticks;
        printf("Nb ticks min = %d \n", nb_ticks_min);
    }    
    printf("Nb ticks  = %d \n", nb_ticks);

    int h_canvas = fig->img->sy - 2*fig->pad[1];
    // On pense a enlever la marge Y pour calculer l'ecart entre tick maj
    // Pos de maxY repere figure = h_canvas - fig->margin[1]
    int h_max = h_canvas - fig->margin[1];
    printf("h max     = %d \n", h_max);

    // int ecart_major = ( h_canvas - fig->margin[1] ) / (nb_interv)  ; 

    int itv_pixels = (itv*h_max) / fig->max_Y;
    printf("Itv px     = %d \n", itv_pixels);

    // Style tick
    int w_tick = 2;
    int w_linegrid = 0.5;
    int long_tick = 9;
    int long_tick_min = 5;
    LineStyle style_tick;
    Init_linestyle(&style_tick, '-', fig->color_axes, w_tick, ' ', ' ');

    int gris_grid[3] = {71, 71, 71};
    LineStyle style_linegrid;
    Init_linestyle(&style_linegrid, ':', gris_grid, w_linegrid, ' ', ' ');

    // Plot ticks
  

    char tickVal[12];

    for (int i = 1; i <= nb_ticks; i++)
    {
        sprintf(tickVal, "%d", i*itv);

        ImageLineEpaisseur(fig->img,\
                        fig->orig[0]-long_tick-2,\
                            fig->orig[1] - i*itv_pixels,\
                        fig->orig[0]-2,\
                            fig->orig[1] - i*itv_pixels,\
                        &style_tick);

        ImageLineEpaisseur(fig->img,\
                        fig->orig[0],\
                            fig->orig[1] - i*itv_pixels,\
                        fig->img->sx,\
                            fig->orig[1] - i*itv_pixels,\
                        &style_linegrid);        


        if (itv_minor != 0) {

            for (int j = 1; j < nb_ticks_min; j++)
            {
                int itv_ytickmin = fig->orig[1] - (i-1)*itv_pixels - j*(itv_pixels/(nb_ticks_min));
                
                ImageLineEpaisseur(fig->img,\
                                fig->orig[0]-long_tick_min-2,\
                                    itv_ytickmin,\
                                fig->orig[0]-2,\
                                    itv_ytickmin,\
                                &style_tick);            
            }
        }

        // printf("Tick val : %s \n", tickVal);
        gdImageStringFT(fig->img, NULL,\
                            GetCouleur(fig->img, style_tick.color), font,\
                                fontsize, 0.,\
                                fig->orig[0]-(long_tick+2)-strlen(tickVal)*fontsize,\
                                fig->orig[1] - i*itv_pixels + fontsize/2,\
                                tickVal);

        // printf("%d\n", i);
    }

    //Avoid memory leaks
    gdFontCacheShutdown();
}

#endif /* PLOTTER_H */