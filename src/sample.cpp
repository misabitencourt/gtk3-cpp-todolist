#include <gtk/gtk.h>
#include<list>
#include<string>

// Types
#include "types/models.h"

// Services
#include "services/todo-service.h"

// Views
#include "views/dialogs.h"
#include "views/main.h"


int main(int argc, char *argv[]) 
{
    gtk_init(&argc, &argv);

    // Show all widgets
    MainWindow::openMainWindow();

    gtk_main();

    return 0;
}
