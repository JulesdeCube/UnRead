
#include "segmentation.h"



/* return a list of int. That represent the ammout of black pixel of each line*/
int * horizontalProjection(GdkPixbuf *pixbuf)
{
    guchar *p;
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);
    int * hp =(int *) malloc( height * sizeof(int));

    for (int i = 0; i < height; ++i)
    {
        hp[i] = 0;
    }

    for(int y = 0; y < height ; ++y)
    {
        for(int x = 0; x < width; ++x)
        {

            p = which_pixels + y * rowstride + x * n_channels;
            // image coming from transform_graylvl.c are either totally black or totally white,
           if (p[0] < 128)
           {
               hp[y] += 1;
           }

        }
    }
    return hp;

}
/* return a list of int. That represent the ammout of black pixel of each collum*/
int * verticalProjection(GdkPixbuf *pixbuf)
{
    guchar *p;
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);
    int * vp =(int *) malloc( width * sizeof(int) );

    for (int i = 0; i < width; ++i)
    {
        vp[i] = 0;
    }
    for(int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            // image coming from transform_graylvl.c are either totally black or totally white,
            if (p[0] < 128) {
                vp[x] += 1;
            }
        }
    }
    return vp;

}
/*take an image (format pixbuf) and save each detected line in a specified directory. A line is detected when every pixel line has a black pixel.  */
void lineSegmentation(GdkPixbuf *pixbuf)
{
    //printf("horizontal proj\n");
    int * hp = horizontalProjection(pixbuf);
    //printf("horizontal projection end\n");
    int a = 0;
    int b = 0;
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);
    GdkPixbuf *pixLine;
    int lineCount = 0;


    for (int j = 0; j < height; ++j)
    {
        if (!hp[j])
        {
            // case when there is not any black pixel and the two line marker are different.
            if (a != b)
            {
                lineCount +=1;
                pixLine = gdk_pixbuf_new_subpixbuf(pixbuf,0,a,width,b-a);

                /* line name is segmentedLine_/line number/ and the format is bmp*/
                char * sg = (char *) malloc( 255 * sizeof(char) );
                char * number = (char *) malloc( 255 * sizeof(char));
                char * t = (char *) malloc( 255 * sizeof(char) );
                char * type = (char *) malloc( 255 * sizeof(char) );
                sprintf(sg,"segmentedLine_");
                sprintf(number, "%d", lineCount);
                sprintf(t, "bmp");
                sprintf(type, ".bmp");
                strcat(sg, number);
                strcat(sg,type);
                //number +=1;
                //printf("saving line\n");
                gdk_pixbuf_save(pixLine,sg,t,NULL,NULL);



                //moving file from UnRead to specific folder.
                char newpath[255] = "./cuted_line/";
                strcat(newpath,sg);
                rename(sg,newpath);

                //printf("moving line,name: %s,to %s\n",sg,newpath);

                a = j;
                b = j;

                free(sg);
                free(number);
                free(t);
                free(type);
            }
            // case when there is not any black pixel but the two line marker are the same. Skip to next line
            else
            {
                a ++;
                b ++;
            }
        }
        // case when there is a black pixel, the first line marker stay to the line start and we increment the second until we reach the end of the line.
        else
        {
            b++;
        }

    }
    free(hp);
}




/*find number of pixel between char */

int charSpacePixel(GdkPixbuf *pixbuf){
    int * vp = verticalProjection(pixbuf);
    int min = 1000;
    int a = 0;
    int b = 0;
    int width = gdk_pixbuf_get_width (pixbuf);
    for (int j = 0; j < width; ++j)
    {
        if (vp[j])//row not full white pixel
        {
            if (a != b)
            {
                if (min > b-a){
                    min = b-a;
                }
                a = 0;
                b = 0;
            }
            else
            {
                a ++;
                b ++;
            }
        }
        else
        {
            b++;
        }
    }
    return min;
    free(vp);
}



/*take an image (format pixbuf) and save each detected Char in a specified directory.
 A Char is detected when every pixel collum has at least one black pixel.
 To avoid name overlap, we add the line number to the char name.
 work the same as the lineSegmentation*/
void charSegmentation(GdkPixbuf *pixbuf,int lineNumber)
{
    //printf("vertical projection start\n");
    int * vp = verticalProjection(pixbuf);
    //printf("vertical projection end\n");
    int a = 0;
    int b = 0;
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);
    GdkPixbuf *pixChar;
    int charCount = 0;



    for (int j = 0; j < width; ++j)
    {
        //printf("black pixel in collum %d: %d\n",j,*(vp+j));
        if (!vp[j])
        {
            if (a != b)
            {

                charCount +=1;
                pixChar = gdk_pixbuf_new_subpixbuf(pixbuf,a,0,b-a,height);

                /* line name is segmentedLine_/line number/ and the format is bmp*/
                char * sg = (char *) malloc( 255 * sizeof(char) );
                char * number = (char *) malloc( 255 * sizeof(char));
                char * number2 = (char *) malloc( 255 * sizeof(char));
                char * t = (char *) malloc( 255 * sizeof(char));
                char * type = (char *) malloc( 255 * sizeof(char));
                sprintf(sg,"segmentedLine_");
                sprintf(number2, "%d_", lineNumber);
                strcat(sg,number2);
                sprintf(number, "%d", charCount);
                sprintf(t, "bmp");
                sprintf(type, ".bmp");
                strcat(sg, number);
                strcat(sg,type);
                //printf("saving line\n");

                gdk_pixbuf_save(pixChar,sg,t,NULL,NULL);



                //moving file from UnRead to specific folder.
                char newpath[255] = "./cuted_char/";
                strcat(newpath,sg);
                rename(sg,newpath);

                a = j;
                b = j;

                free(sg);
                free(number);
                free(number2);
                free(t);
                free(type);

            }
            else
            {
                a ++;
                b ++;
            }
        }
        else
        {
            b++;
        }
    }
    free(vp);
}
//same sub function in load.c to create a gtk object from an image.
GtkWidget* create_image2 (char path[255])
{
    GtkWidget *image;
    image = gtk_image_new_from_file (path);
    return image;
}

//Main segmentation function. Divide a black and white image in line, then Divide every line in char. Output qre stocked in ./cuted_char/
void mainSegmentation(GtkWidget* image_to_change)
{
    //printf("segmentation start\n");
    GdkPixbuf *pixbuf;
    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image_to_change);
    //printf("line seg\n");
    lineSegmentation(pixbuf);
    //printf("line seg end\n");

    int c = 1;

    DIR *d;
    struct dirent *dir;
    d = opendir("./cuted_line");
    char fileName[269];
    GtkWidget *lineImage;
    GdkPixbuf *pixbuf2;
    if (d)
    {
        //use dirent.h to find every line
        while ((dir = readdir(d)) != NULL) {
            //printf("line number:%d\n", c);

            sprintf(fileName, "./cuted_line/%s", dir->d_name);
            //printf("%s\n",fileName);
            if (d)
                lineImage = create_image2(fileName);
            pixbuf2 = gtk_image_get_pixbuf((GtkImage *) lineImage);
            if (GDK_IS_PIXBUF(pixbuf2)) {
                //printf("char seg\n");



                charSegmentation(pixbuf2, c);
                //printf("char seg end\n");
                c += 1;
            }
        }
        closedir(d);
    }

}
