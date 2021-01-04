#include<iostream>
#include<string>
#include<vector>

#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

/** Uploads the image for a given path
 *
 * @param path The pathname for the image
 * @return Mat The image
 *
 * @throw CustomError Thrown if image requested is not found
 */

Mat upload_img(string path){
    //uploading the image for the given path
    Mat image = imread(path, IMREAD_COLOR);

    if(!image.data){
        throw "Image path is not valid\n";
    }

    return image;
}

Mat binarisation(Mat image){
    //set image to be black and white
    Mat gray_image;
    Mat final;

    if(!image.data){
        throw "Image path is not valid\n";
    }

    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    adaptiveThreshold(gray_image, final, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 75, 50);
    bitwise_not(final, final);

    return final;
}

Mat noise_removal(Mat image){
    // remove the potential noise form the image
    if(!image.data){
        throw "Image path is not valid\n";
    }
    Mat final_img;

   Size size(3,3);
   GaussianBlur(image,final_img,size,0);

   Mat ero(3,3,CV_8U,Scalar(1));
   morphologyEx(final_img,final_img,MORPH_OPEN, ero);

    return final_img;
}

Mat crop(Mat image){
    // crop and rotate the image to the smallest horizontal rectangle
    if(!image.data){
        throw "Image path is not valid\n";
    }

     Mat output=image.clone();

     vector<Point> points;
     Mat_<uchar>::iterator it = image.begin<uchar>();
     Mat_<uchar>::iterator end = image.end<uchar>();
     for (; it != end; ++it)
       if (*it)
         points.push_back(it.pos());

     RotatedRect box = minAreaRect(Mat(points));

     double angle = box.angle;
     if (angle < -45.)
       angle += 90.;

     Point2f vertices[4];
     box.points(vertices);
     for(int i = 0; i < 4; ++i)
       line(image, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0), 1, LINE_AA);



     Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);

     Mat rotated;
     warpAffine(output, rotated, rot_mat, image.size(), INTER_CUBIC);



     Size box_size = box.size;
     if (box.angle < -45.)
       swap(box_size.width, box_size.height);
     Mat cropped;

     getRectSubPix(rotated, box_size, box.center, cropped);


    return cropped;
}

class comparator{
    //comprator for sorting to be made as a function
public:
    bool operator()(vector<Point> c1,vector<Point>c2){
        return boundingRect( Mat(c1)).x<boundingRect( Mat(c2)).x;
    }
};

void extract_contours(Mat image){
    //extarcting and preparing the signs to be read
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours( image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_TC89_KCOS, Point(0, 0));

    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );

    for( int i = 0; i <(int)contours.size(); i++ ){
         approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
    }

    vector<vector<Point> > validContours;
       for (int i=0;i<(int)contours_poly.size();i++){

           Rect r = boundingRect(Mat(contours_poly[i]));
           if(r.area()<200)
               continue;  //to be checked how can be improved

           bool inside = false;
           for(int j=0;j<(int)contours_poly.size();j++){
               if(j==i)continue;

               Rect r2 = boundingRect(Mat(contours_poly[j]));
               if(r2.area()<100||r2.area()<r.area())continue;
               if(r.x>r2.x&&r.x+r.width<r2.x+r2.width&&
                   r.y>r2.y&&r.y+r.height<r2.y+r2.height){

                   inside = true;
               }
           }
           if(inside)
                continue;
           validContours.push_back(contours_poly[i]);
       }

       sort(contours_poly.begin(),contours_poly.end(),comparator());

       //Loop through all contours to extract
        for( int i = 0; i< (int)contours_poly.size(); i++ ){

           Rect r = boundingRect( Mat(contours_poly[i]) );


           Mat mask = Mat::zeros(image.size(), CV_8UC1);
           //Draw mask onto image
           drawContours(mask, contours_poly, i, Scalar(255), FILLED);

           //Check for equal sign (2 dashes on top of each other) and merge
           if(i+1< (int)contours_poly.size()){
               Rect r2 = boundingRect( Mat(contours_poly[i+1]) );
               if(abs(r2.x-r.x)<20){
                   //Draw mask onto image
                   drawContours(mask, contours_poly, i+1, Scalar(255), FILLED);
                   i++;
                   int minX = min(r.x,r2.x);
                   int minY = min(r.y,r2.y);
                   int maxX =  max(r.x+r.width,r2.x+r2.width);
                   int maxY = max(r.y+r.height,r2.y+r2.height);
                   r = Rect(minX,minY,maxX - minX,maxY-minY);

               }
           }
           //Copy
            Mat extractPic;
            //Extract the character using the mask
            image.copyTo(extractPic,mask);
            Mat resizedPic = extractPic(r);

           Mat image=resizedPic.clone();

           resize(image, image, Size(28,28), INTER_CUBIC);  //other possible interpolations to be tried: INTER_NEAREST, INTER_LINEAR, INTER_AREA

           //Show image
           imshow("image",image);
           waitKey(0);
           stringstream searchMask;
           searchMask<<i<<".jpg";
           imwrite(searchMask.str(),image);


        }

}

void display_prepocessing(string path){
    // dispalay the extracting process, for testing and debugging
    Mat image= upload_img(path);
    //image = noise_removal(image);
    image = binarisation(image);
    image = crop(image);
    //image = noise_removal(image);

    // improvement of dilation if possible
 /*  int dilation_size=0.5;
    Mat element = getStructuringElement(  MORPH_RECT,
                         Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                         Point( dilation_size, dilation_size ) );
    dilate( image, image, element );*/

    const char* source_window = "Source";
    namedWindow( source_window, WINDOW_NORMAL );
    resizeWindow(source_window, 1000, 800);
    imshow( source_window, image );

    extract_contours(image);

    waitKey(0);
}

