//
// Created by https://github.com/AlexBychek
//

#include <ui.h>
#include <filesystem>
#include <iostream>

UserInterface::UserInterface()
{
    if (!std::filesystem::exists("temp"))
    {
        std::filesystem::create_directory("temp");
    }

    gtk_init(nullptr, nullptr);

    mWindow_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mWindow_), "ImageProcessor");
    gtk_window_set_default_size(GTK_WINDOW(mWindow_), 1280, 720);
    g_signal_connect(mWindow_, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    mImage_ = gtk_image_new();

    vbox_ = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    createMenuBar();

    mScrolledWindow_ = gtk_scrolled_window_new(nullptr, nullptr);

    gtk_container_add(GTK_CONTAINER(mScrolledWindow_), mImage_);
    gtk_box_pack_start(GTK_BOX(vbox_), mScrolledWindow_, TRUE, TRUE, 0);

    grid_ = gtk_grid_new();

    createResizeBox();
    createRotateBox();
    createProcessingBox();
    createFileInfoBox();

    gtk_grid_set_column_spacing(GTK_GRID(grid_), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid_), 10);

    gtk_container_add(GTK_CONTAINER(vbox_), grid_);

    gtk_container_add(GTK_CONTAINER(mWindow_), vbox_);

    gtk_widget_show_all(mWindow_);
}

void UserInterface::createResizeBox()
{
    resizeGroupBox_ = gtk_frame_new("Resize");
    gtk_container_set_border_width(GTK_CONTAINER(resizeGroupBox_), 10);

    resizeGrid_ = gtk_grid_new();

    resizeAspectRatioLabel_ = gtk_label_new("aspect ratio");

    resizeAspectRatioCheckbox_ = gtk_check_button_new_with_label("AspRat");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(resizeAspectRatioCheckbox_), TRUE);

    resizeLabelWeight_ = gtk_label_new("weight");
    resizeInputWeight_ = gtk_spin_button_new_with_range(0, 10000, 1);
    resizeLabelHeight_ = gtk_label_new("height");
    resizeInputHeight_ = gtk_spin_button_new_with_range(0, 10000, 1);
    resizeButton_ = gtk_button_new_with_label("resize");

    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeLabelWeight_, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeInputWeight_, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeLabelHeight_, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeInputHeight_, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeAspectRatioLabel_, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeAspectRatioCheckbox_, 4, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(resizeGrid_), resizeButton_, 3, 1, 2, 1);

    gtk_grid_set_column_spacing(GTK_GRID(resizeGrid_), 10);
    gtk_grid_set_row_spacing(GTK_GRID(resizeGrid_), 10);

    gtk_container_set_border_width(GTK_CONTAINER(resizeGrid_), 10);

    gtk_container_add(GTK_CONTAINER(resizeGroupBox_), resizeGrid_);

    gtk_grid_attach(GTK_GRID(grid_), resizeGroupBox_, 1, 0, 1, 1);

    g_signal_connect(resizeButton_, "clicked", G_CALLBACK(resizeImage), this);

    gtk_widget_set_sensitive(resizeGroupBox_, FALSE);
}

void UserInterface::createRotateBox()
{
    rotateGroupBox_ = gtk_frame_new("Rotate");
    gtk_container_set_border_width(GTK_CONTAINER(rotateGroupBox_), 10);

    rotateGrid_ = gtk_grid_new();

    rotateLabel_ = gtk_label_new("degree");
    rotateInputDegree_ = gtk_spin_button_new_with_range(0, 360, 1);
    rotateButton_ = gtk_button_new_with_label("rotate");

    gtk_grid_attach(GTK_GRID(rotateGrid_), rotateLabel_, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(rotateGrid_), rotateInputDegree_, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(rotateGrid_), rotateButton_, 1, 1, 2, 1);

    gtk_grid_set_column_spacing(GTK_GRID(rotateGrid_), 10);
    gtk_grid_set_row_spacing(GTK_GRID(rotateGrid_), 10);

    gtk_container_set_border_width(GTK_CONTAINER(rotateGrid_), 10);

    gtk_container_add(GTK_CONTAINER(rotateGroupBox_), rotateGrid_);

    gtk_grid_attach(GTK_GRID(grid_), rotateGroupBox_, 2, 0, 1, 1);

    g_signal_connect(rotateButton_, "clicked", G_CALLBACK(rotateImage), this);

    gtk_widget_set_sensitive(rotateGroupBox_, FALSE);
}

void UserInterface::createProcessingBox()
{
    processingGroupBox_ = gtk_frame_new("Processing");
    gtk_container_set_border_width(GTK_CONTAINER(processingGroupBox_), 10);

    processingGrid_ = gtk_grid_new();

    flopButton_ = gtk_button_new_with_label("flop");
    negativeButton_ = gtk_button_new_with_label("negative");
    modulateButton_ = gtk_button_new_with_label("modulate");

    blurLabel_ = gtk_label_new("sigma");
    blurSlider_ = gtk_button_new_with_label("blur");
    blurButton_ = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);

    gtk_grid_attach(GTK_GRID(processingGrid_), flopButton_, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(processingGrid_), blurLabel_, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(processingGrid_), blurButton_, 2, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(processingGrid_), blurSlider_, 2, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(processingGrid_), modulateButton_, 5, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(processingGrid_), negativeButton_, 5, 1, 1, 1);

    gtk_grid_set_column_spacing(GTK_GRID(processingGrid_), 10);
    gtk_grid_set_row_spacing(GTK_GRID(processingGrid_), 10);

    gtk_container_set_border_width(GTK_CONTAINER(processingGrid_), 10);

    gtk_container_add(GTK_CONTAINER(processingGroupBox_), processingGrid_);

    gtk_grid_attach(GTK_GRID(grid_), processingGroupBox_, 3, 0, 1, 1);

    g_signal_connect(flopButton_, "clicked", G_CALLBACK(flopImage), this);
    g_signal_connect(blurSlider_, "clicked", G_CALLBACK(blurImage), this);
    g_signal_connect(negativeButton_, "clicked", G_CALLBACK(negativeImage), this);
    g_signal_connect(modulateButton_, "clicked", G_CALLBACK(modulateImage), this);

    gtk_widget_set_sensitive(processingGroupBox_, FALSE);
}

void UserInterface::createMenuBar()
{
    mMenuBar_ = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox_), mMenuBar_, false, TRUE, 0);

    mFileMenu_ = gtk_menu_new();
    mEditMenu_ = gtk_menu_new();
    mFileMenuItem_ = gtk_menu_item_new_with_label("File");
    mEditMenuItem_ = gtk_menu_item_new_with_label("Edit");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mFileMenuItem_), mFileMenu_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mMenuBar_), mFileMenuItem_);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mEditMenuItem_), mEditMenu_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mMenuBar_), mEditMenuItem_);

    mOpenMenuItem_ = gtk_menu_item_new_with_label("Open");
    mResetMenuItem_ = gtk_menu_item_new_with_label("Reset");
    mClearMenuItem_ = gtk_menu_item_new_with_label("Clear");
    mSaveMenuItem_ = gtk_menu_item_new_with_label("Save");
    mSaveAsMenuItem_ = gtk_menu_item_new_with_label("SaveAs");
    mCloseMenuItem_ = gtk_menu_item_new_with_label("Close");

    mWatermarkMenuItem_ = gtk_menu_item_new_with_label("Watermark");
    mFlopMenuItem_ = gtk_menu_item_new_with_label("Flop");
    mModulateMenuItem_ = gtk_menu_item_new_with_label("Modulate");
    mNegativeMenuItem_ = gtk_menu_item_new_with_label("Negative");

    gtk_widget_set_sensitive(mSaveMenuItem_, FALSE);
    gtk_widget_set_sensitive(mSaveAsMenuItem_, FALSE);
    gtk_widget_set_sensitive(mResetMenuItem_, FALSE);
    gtk_widget_set_sensitive(mClearMenuItem_, FALSE);

    gtk_widget_set_sensitive(mWatermarkMenuItem_, FALSE);
    gtk_widget_set_sensitive(mFlopMenuItem_, FALSE);
    gtk_widget_set_sensitive(mModulateMenuItem_, FALSE);
    gtk_widget_set_sensitive(mNegativeMenuItem_, FALSE);

    gtk_menu_shell_append(GTK_MENU_SHELL(mFileMenu_), mOpenMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mFileMenu_), mResetMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mFileMenu_), mClearMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mFileMenu_), mSaveMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mFileMenu_), mSaveAsMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mFileMenu_), mCloseMenuItem_);

    gtk_menu_shell_append(GTK_MENU_SHELL(mEditMenu_), mWatermarkMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mEditMenu_), mFlopMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mEditMenu_), mModulateMenuItem_);
    gtk_menu_shell_append(GTK_MENU_SHELL(mEditMenu_), mNegativeMenuItem_);
    g_signal_connect(mOpenMenuItem_, "activate", G_CALLBACK(onOpenMenuItemActivate), this);
    g_signal_connect(mResetMenuItem_, "activate", G_CALLBACK(resetImage), this);
    g_signal_connect(mClearMenuItem_, "activate", G_CALLBACK(clearImage), this);
    g_signal_connect(mSaveMenuItem_, "activate", G_CALLBACK(onSaveImage), this);
    g_signal_connect(mSaveAsMenuItem_, "activate", G_CALLBACK(onSaveImageAs), this);
    g_signal_connect(mCloseMenuItem_, "activate", G_CALLBACK(gtk_main_quit), nullptr);

    g_signal_connect(mWatermarkMenuItem_, "activate", G_CALLBACK(onWatermarkEditor), this);
    g_signal_connect(mFlopMenuItem_, "activate", G_CALLBACK(flopImage), this);
    g_signal_connect(mModulateMenuItem_, "activate", G_CALLBACK(modulateImage), this);
    g_signal_connect(mNegativeMenuItem_, "activate", G_CALLBACK(negativeImage), this);
}

void UserInterface::createFileInfoBox()
{
    fileInfoGroupBox_ = gtk_frame_new("FileInfo");
    gtk_container_set_border_width(GTK_CONTAINER(fileInfoGroupBox_), 10);

    fileInfoGrid_ = gtk_grid_new();

    fileLabelPathLabel_ = gtk_label_new("Path: ");
    fileLabelSizeLabel_ = gtk_label_new("Size: ");
    fileLabelWhLabel_ =   gtk_label_new("WxH:  ");

    fileInfoPathLabel_ = gtk_label_new("file is not open");
    fileInfoSizeLabel_ = gtk_label_new("file is not open");
    fileInfoWhLabel_ =   gtk_label_new("file is not open");

    gtk_label_set_line_wrap(GTK_LABEL(fileInfoPathLabel_), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(fileInfoPathLabel_), PANGO_WRAP_WORD_CHAR);

    gtk_grid_attach(GTK_GRID(fileInfoGrid_), fileLabelPathLabel_, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(fileInfoGrid_), fileLabelSizeLabel_, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(fileInfoGrid_), fileLabelWhLabel_, 1, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(fileInfoGrid_), fileInfoPathLabel_, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(fileInfoGrid_), fileInfoSizeLabel_, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(fileInfoGrid_), fileInfoWhLabel_, 2, 2, 1, 1);

    gtk_grid_set_column_spacing(GTK_GRID(fileInfoGrid_), 10);
    gtk_grid_set_row_spacing(GTK_GRID(fileInfoGrid_), 10);

    gtk_container_set_border_width(GTK_CONTAINER(fileInfoGrid_), 10);

    gtk_container_add(GTK_CONTAINER(fileInfoGroupBox_), fileInfoGrid_);

    gtk_grid_attach(GTK_GRID(grid_), fileInfoGroupBox_, 4, 0, 1, 1);
}

void UserInterface::run()
{
    gtk_main();
}

void UserInterface::updateImage()
{
    std::string tmpFile("temp/1.png");
    workImage_.saveAs(tmpFile);

    gtk_image_set_from_file(GTK_IMAGE(mImage_), tmpFile.c_str());
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(resizeInputWeight_), workImage_.getWeight() );
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(resizeInputHeight_), workImage_.getHeight() );
}

void UserInterface::setEnableElementProcessing( bool status )
{
    if (status)
    {
        gtk_widget_set_sensitive(mSaveMenuItem_, TRUE);
        gtk_widget_set_sensitive(mSaveAsMenuItem_, TRUE);
        gtk_widget_set_sensitive(mResetMenuItem_, TRUE);
        gtk_widget_set_sensitive(mClearMenuItem_, TRUE);
        gtk_widget_set_sensitive(resizeGroupBox_, TRUE);
        gtk_widget_set_sensitive(rotateGroupBox_, TRUE);
        gtk_widget_set_sensitive(processingGroupBox_, TRUE);
        gtk_widget_set_sensitive(mWatermarkMenuItem_, TRUE);
        gtk_widget_set_sensitive(mFlopMenuItem_, TRUE);
        gtk_widget_set_sensitive(mModulateMenuItem_, TRUE);
        gtk_widget_set_sensitive(mNegativeMenuItem_, TRUE);

    }
    else
    {
        gtk_widget_set_sensitive(mSaveMenuItem_, FALSE);
        gtk_widget_set_sensitive(mSaveAsMenuItem_, FALSE);
        gtk_widget_set_sensitive(mResetMenuItem_, FALSE);
        gtk_widget_set_sensitive(mClearMenuItem_, FALSE);
        gtk_widget_set_sensitive(resizeGroupBox_, FALSE);
        gtk_widget_set_sensitive(rotateGroupBox_, FALSE);
        gtk_widget_set_sensitive(processingGroupBox_, FALSE);
        gtk_widget_set_sensitive(mWatermarkMenuItem_, FALSE);
        gtk_widget_set_sensitive(mFlopMenuItem_, FALSE);
        gtk_widget_set_sensitive(mModulateMenuItem_, FALSE);
        gtk_widget_set_sensitive(mNegativeMenuItem_, FALSE);

    }
}

void UserInterface::onOpenMenuItemActivate(GtkMenuItem* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(interface->mWindow_), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, nullptr);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        interface->workImage_.load(std::string(filename) );
        g_free(filename);
        interface->updateImage();

        gtk_label_set_text(GTK_LABEL(interface->fileInfoPathLabel_), interface->workImage_.absolutePath().c_str());
        gtk_label_set_text(GTK_LABEL(interface->fileInfoSizeLabel_), interface->workImage_.fileSize().c_str());
        gtk_label_set_text(GTK_LABEL(interface->fileInfoWhLabel_), interface->workImage_.imageSize().c_str());

        interface->setEnableElementProcessing(true);
    }

    gtk_widget_destroy(dialog);
}

void UserInterface::onSaveImage(GtkMenuItem* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    interface->workImage_.save();
}

void UserInterface::onSaveImageAs(GtkMenuItem* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(interface->mWindow_), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, nullptr);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        interface->workImage_.saveAs(std::string(filename) );
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void UserInterface::resizeImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);

    int resize_weight = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(interface->resizeInputWeight_));
    int resize_height = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(interface->resizeInputHeight_));

    gboolean state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(interface->resizeAspectRatioCheckbox_));

    interface->workImage_.resize(resize_weight, resize_height, state);
    interface->updateImage();
}

void UserInterface::rotateImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);

    int rotate_degree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(interface->rotateInputDegree_));

    interface->workImage_.rotate(rotate_degree);
    interface->updateImage();
}

void UserInterface::flopImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    interface->workImage_.flop();
    interface->updateImage();
}

void UserInterface::negativeImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    interface->workImage_.negative();
    interface->updateImage();
}

void UserInterface::modulateImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    interface->workImage_.modulate();
    interface->updateImage();
}

void UserInterface::blurImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    int blur_step = gtk_range_get_value(GTK_RANGE(interface->blurButton_));

    interface->workImage_.blur(blur_step);
    interface->updateImage();
}

void UserInterface::resetImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    interface->workImage_.reset();
    interface->updateImage();
}

void UserInterface::clearImage(GtkWidget* widget, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    interface->workImage_ = Image();
    interface->setEnableElementProcessing(false);
    gtk_image_clear(GTK_IMAGE(interface->mImage_));

    gtk_label_set_text(GTK_LABEL(interface->fileInfoPathLabel_), "file is not open");
    gtk_label_set_text(GTK_LABEL(interface->fileInfoSizeLabel_), "file is not open");
    gtk_label_set_text(GTK_LABEL(interface->fileInfoWhLabel_), "file is not open");
}

void UserInterface::createWaterMarkWindow()
{

    watermarkWindow_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(watermarkWindow_), "WaterMarkEditor");
    gtk_window_set_default_size(GTK_WINDOW(watermarkWindow_), 400, 100);
    g_signal_connect(watermarkWindow_, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    watermarkVbox_ = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    watermarkImageWidget_ = gtk_image_new();

    gtk_container_add(GTK_CONTAINER(watermarkVbox_), watermarkImageWidget_);

    watermarkGroupBox_ = gtk_frame_new("WaterMarkEdit");
    gtk_container_set_border_width(GTK_CONTAINER(watermarkGroupBox_), 10);

    watermarkWindowGrid_ = gtk_grid_new();

    pathLabel_ = gtk_label_new("path:");

    gtk_label_set_line_wrap(GTK_LABEL(pathLabel_), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(pathLabel_), PANGO_WRAP_WORD_CHAR);

    scaleLabel_ = gtk_label_new("scale");
    scaleSlider_ = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
    gtk_range_set_value(GTK_RANGE(scaleSlider_), 100);

    xOffsetLabel_ = gtk_label_new("xOffset");
    xOffsetInput_ = gtk_spin_button_new_with_range(0, 10000, 1);
    yOffsetLabel_ = gtk_label_new("yOffset");
    yOffsetInput_ = gtk_spin_button_new_with_range(0, 10000, 1);
    watermarkButton_ = gtk_button_new_with_label("Add");

    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), pathLabel_, 1, 0, 5, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), scaleLabel_, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), scaleSlider_, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), xOffsetLabel_, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), xOffsetInput_, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), yOffsetLabel_, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), yOffsetInput_, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(watermarkWindowGrid_), watermarkButton_, 1, 4, 5, 1);

    gtk_grid_set_column_spacing(GTK_GRID(watermarkWindowGrid_), 10);
    gtk_grid_set_row_spacing(GTK_GRID(watermarkWindowGrid_), 10);

    gtk_container_set_border_width(GTK_CONTAINER(watermarkWindowGrid_), 10);

    gtk_container_add(GTK_CONTAINER(watermarkGroupBox_), watermarkWindowGrid_);
    gtk_container_add(GTK_CONTAINER(watermarkVbox_), watermarkGroupBox_);
    gtk_container_add(GTK_CONTAINER(watermarkWindow_), watermarkVbox_);

    g_signal_connect(watermarkButton_, "clicked", G_CALLBACK(addWatermarkImage), this);
}

void UserInterface::onWatermarkEditor(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Open Watermark File", GTK_WINDOW(interface->mWindow_), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, nullptr);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_widget_destroy(dialog);
        interface->watermark_.load(std::string(filename));

        interface->createWaterMarkWindow();

        std::string tmpFile("temp/2.png");
        Watermark watermark_tmp = interface->watermark_;
        watermark_tmp.resize(150, 150, true);
        watermark_tmp.saveAs(tmpFile);

        gtk_image_set_from_file(GTK_IMAGE(interface->watermarkImageWidget_), tmpFile.c_str());

        gtk_label_set_text(GTK_LABEL(interface->pathLabel_), std::string("path: " + std::string(filename)).c_str() );
        g_free(filename);
        gtk_widget_show_all(interface->watermarkWindow_);
        gtk_main();
    }
}

void UserInterface::addWatermarkImage(GtkWidget* menu_item, gpointer user_data)
{
    UserInterface* interface = static_cast<UserInterface*>(user_data);

    uint32_t scale   = gtk_range_get_value(GTK_RANGE(interface->scaleSlider_));
    uint32_t xOffset = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(interface->xOffsetInput_));
    uint32_t yOffset = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(interface->yOffsetInput_));

    interface->watermark_.setParams( scale, xOffset, yOffset );
    interface->watermark_.addWatermark(interface->workImage_);
    
    interface->updateImage();

    gtk_window_close(GTK_WINDOW(interface->watermarkWindow_));
}

