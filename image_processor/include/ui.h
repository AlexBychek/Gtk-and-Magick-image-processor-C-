//
// Created by https://github.com/AlexBychek
//

#ifndef IMAGEPROCESSOR_UI_H
#define IMAGEPROCESSOR_UI_H

#include <gtk/gtk.h>
#include <image.h>
#include <watermark.h>

class UserInterface
{
private:
    GtkWidget* mWindow_;
    GtkWidget* vbox_;
    GtkWidget* grid_;

    Image workImage_;
    Watermark watermark_;
public:
    UserInterface();
    void run();

private:
    void updateImage();

    /* Image Frame */

    GtkWidget* mImage_;
    GtkWidget* mScrolledWindow_;

    /* MenuBar */

    GtkWidget* mMenuBar_;
    GtkWidget* mFileMenu_;
    GtkWidget* mFileMenuItem_;
    GtkWidget* mEditMenu_;
    GtkWidget* mEditMenuItem_;

    GtkWidget* mOpenMenuItem_;
    GtkWidget* mResetMenuItem_;
    GtkWidget* mClearMenuItem_;
    GtkWidget* mSaveMenuItem_;
    GtkWidget* mSaveAsMenuItem_;
    GtkWidget* mCloseMenuItem_;
    GtkWidget* mWatermarkMenuItem_;
    GtkWidget* mFlopMenuItem_;
    GtkWidget* mModulateMenuItem_;
    GtkWidget* mNegativeMenuItem_;

    void createMenuBar();

    /* Resize Box */

    GtkWidget* resizeGroupBox_;
    GtkWidget* resizeGrid_;
    GtkWidget* resizeAspectRatioLabel_;
    GtkWidget* resizeAspectRatioCheckbox_;
    GtkWidget* resizeLabelWeight_;
    GtkWidget* resizeInputWeight_;
    GtkWidget* resizeLabelHeight_;
    GtkWidget* resizeInputHeight_;
    GtkWidget* resizeButton_;

    void createResizeBox();

    /* Rotate Box */

    GtkWidget* rotateGroupBox_;
    GtkWidget* rotateGrid_;

    GtkWidget* rotateLabel_;
    GtkWidget* rotateInputDegree_;
    GtkWidget* rotateButton_;

    void createRotateBox();

    /* Processing Box */

    GtkWidget* processingGroupBox_;
    GtkWidget* processingGrid_;

    GtkWidget* flopButton_;
    GtkWidget* negativeButton_;
    GtkWidget* modulateButton_;

    GtkWidget* blurLabel_;
    GtkWidget* blurSlider_;
    GtkWidget* blurButton_;

    void createProcessingBox();

    /* FileInfo Box */

    GtkWidget* fileInfoGroupBox_;
    GtkWidget* fileInfoGrid_;

    GtkWidget* fileLabelPathLabel_;
    GtkWidget* fileLabelSizeLabel_;
    GtkWidget* fileLabelWhLabel_;

    GtkWidget* fileInfoPathLabel_;
    GtkWidget* fileInfoSizeLabel_;
    GtkWidget* fileInfoWhLabel_;

    void createFileInfoBox();

    /* WaterMark Window */

    GtkWidget* watermarkWindow_;
    GtkWidget* watermarkGroupBox_;
    GtkWidget* watermarkWindowGrid_;
    GtkWidget* watermarkVbox_;
    GtkWidget* watermarkImageWidget_;

    GtkWidget* pathLabel_;
    GtkWidget* scaleLabel_;
    GtkWidget* scaleSlider_;
    GtkWidget* opacityLabel_;
    GtkWidget* opacitySlider_;
    GtkWidget* xOffsetLabel_;
    GtkWidget* xOffsetInput_;
    GtkWidget* yOffsetLabel_;
    GtkWidget* yOffsetInput_;
    GtkWidget* watermarkButton_;


    void createWaterMarkWindow();
    void close();

    /* ///////  */

    void setEnableElementProcessing( bool status );

    static void onOpenMenuItemActivate(GtkMenuItem* menuItem, gpointer user_data);
    static void onSaveImage(GtkMenuItem* menuItem, gpointer user_data);
    static void onSaveImageAs(GtkMenuItem* menuItem, gpointer user_data);
    static void resizeImage(GtkWidget* widget, gpointer user_data);
    static void rotateImage(GtkWidget* widget, gpointer user_data);

    static void onWatermarkEditor(GtkWidget* menuItem, gpointer user_data);
    static void addWatermarkImage(GtkWidget* menuItem, gpointer user_data);
    static void flopImage(GtkWidget* widget, gpointer user_data);
    static void negativeImage(GtkWidget* widget, gpointer user_data);
    static void modulateImage(GtkWidget* menuItem, gpointer user_data);
    static void blurImage(GtkWidget* menuItem, gpointer user_data);
    static void resetImage(GtkWidget* menuItem, gpointer user_data);
    static void clearImage(GtkWidget* menuItem, gpointer user_data);
};

#endif //IMAGEPROCESSOR_UI_H