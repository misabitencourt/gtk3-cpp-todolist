#define APP_MAIN_WINDOW_WIDTH 400
#define APP_MAIN_WINDOW_HEIGHT 800
#define SUCCESS_COLOR "#99DD99"

namespace MainWindow
{
    // Main widget pointers
    GtkWidget *mainWindow = nullptr;
    GtkWidget *mainWindowContainer = nullptr;
    GtkWidget *(*mainWindowRefresh)();
    GtkWidget *todoInputText;
    int inEdition = 0;

    // Button events
    void mainWindowViewTodoListSaveClicked(GtkWidget *widget, gpointer data)
    {
        GtkEntry *entry = GTK_ENTRY(data);
        const gchar *text = gtk_entry_get_text(entry);
        Todo todoDto;
        todoDto.description = (char *)text;
        if (inEdition)
        {
            todoDto.id = inEdition;
            TodoService::todolistUpdate(&todoDto);
        }
        else
        {
            TodoService::todolistSave(&todoDto);
        }
        inEdition = 0;
        mainWindowRefresh();
        gtk_widget_show_all(mainWindowContainer);
    }

    void mainWindowViewTodoListEditClicked(GtkWidget *widget, int id)
    {
        Todo *todo = TodoService::todolistLoad(id);
        inEdition = id;
        g_print("Editing %i %s\n", todo->id, todo->description);
        gtk_entry_set_text(GTK_ENTRY(todoInputText), todo->description);
    }

    void mainWindowViewTodoListDeleteClicked(GtkWidget *widget, int id)
    {
        TodoService::todolistDelete(id);
        mainWindowRefresh();
        gtk_widget_show_all(mainWindowContainer);
    }

    // Render function
    GtkWidget *createMainWindowView()
    {
        GtkWidget *list_box;
        GtkWidget *row;
        GtkWidget *hbox;
        GtkWidget *label;

        mainWindowRefresh = createMainWindowView;

        // Creates a new window
        if (mainWindow == nullptr)
        {
            mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_title(GTK_WINDOW(mainWindow), "Todo List");
            gtk_window_set_default_size(GTK_WINDOW(mainWindow), APP_MAIN_WINDOW_WIDTH, APP_MAIN_WINDOW_HEIGHT);
            g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        }
        else
        {
            gtk_widget_destroy(mainWindowContainer);
        }

        GtkWidget *windowContainer;
        windowContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        mainWindowContainer = windowContainer;
        gtk_container_add(GTK_CONTAINER(mainWindow), windowContainer);

        GtkWidget *todoFormContainer;
        todoFormContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_container_add(GTK_CONTAINER(windowContainer), todoFormContainer);
        
        GtkWidget *inputVbox;
        inputVbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_set_size_request(inputVbox, 250, -1);
        gtk_container_add(GTK_CONTAINER(todoFormContainer), inputVbox);
        todoInputText = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(inputVbox), todoInputText, TRUE, TRUE, 0);

        GtkWidget *saveBtn;
        saveBtn = gtk_button_new_with_label("Save");
        gtk_widget_set_size_request(saveBtn, 80, -1);
        gtk_container_add(GTK_CONTAINER(todoFormContainer), saveBtn);
        g_signal_connect(saveBtn, "clicked", G_CALLBACK(mainWindowViewTodoListSaveClicked), todoInputText);

        GtkWidget *cancelBtn;
        cancelBtn = gtk_button_new_with_label("Cancel");
        gtk_widget_set_size_request(cancelBtn, 80, -1);
        gtk_container_add(GTK_CONTAINER(todoFormContainer), cancelBtn);

        // // Creates a new GtkListBox
        list_box = gtk_list_box_new();
        gtk_container_add(GTK_CONTAINER(windowContainer), list_box);

        // // Creates and add rows to the GtkListBox
        int i = 0;
        for (std::list<Todo>::iterator it = todoListRepository.begin(); it != todoListRepository.end(); ++it)
        {
            row = gtk_list_box_row_new();
            hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

            // Column 1
            gchar *label_text1 = g_strdup_printf(it->description, i);
            label = gtk_label_new(label_text1);
            gtk_widget_set_size_request(label, 250, -1);
            gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
            g_free(label_text1);

            // Column 2
            GtkWidget *editBtn = gtk_button_new_with_label("Edit");
            gtk_widget_set_size_request(saveBtn, 80, -1);
            gtk_box_pack_start(GTK_BOX(hbox), editBtn, TRUE, TRUE, 0);
            g_signal_connect(editBtn, "clicked", G_CALLBACK(mainWindowViewTodoListEditClicked), it->id);

            // Column 3
            GtkWidget *removeBtn = gtk_button_new_with_label("Remove");
            gtk_widget_set_size_request(removeBtn, 80, -1);
            gtk_box_pack_start(GTK_BOX(hbox), removeBtn, TRUE, TRUE, 0);
            int index = i;
            g_signal_connect(removeBtn, "clicked", G_CALLBACK(mainWindowViewTodoListDeleteClicked), it->id);

            gtk_container_add(GTK_CONTAINER(row), hbox);
            gtk_container_add(GTK_CONTAINER(list_box), row);
            i++;
        }

        return mainWindow;
    }

    // Open function
    void openMainWindow()
    {
        gtk_widget_show_all(createMainWindowView());
    }
}
