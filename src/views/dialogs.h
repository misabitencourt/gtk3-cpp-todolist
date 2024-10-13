


static void showDialogMessage(char * message, GtkWindow * parent)
{
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget * dialog = gtk_message_dialog_new (parent,
                                    flags,
                                    NULL,
                                    GTK_BUTTONS_CLOSE,
                                    message,
                                    NULL,
                                    NULL);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}