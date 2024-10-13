int todoListRepositorySequence = 0;
std::list<Todo> todoListRepository;


namespace TodoService
{
    int todolistSave(Todo * dto)
    {
        Todo newOne;
        newOne.id = ++todoListRepositorySequence;
        newOne.description = malloc(sizeof(char) * strlen(dto->description));
        strcpy(newOne.description, dto->description);
        todoListRepository.push_back(newOne);

        return newOne.id;
    }

    Todo * todolistLoad(int id)
    {
        std::list<Todo>::iterator it = todoListRepository.begin();
        for (std::list<Todo>::iterator item = todoListRepository.begin(); item != todoListRepository.end(); ++item)
        {
            if (item->id == id)
            {
                return &(*item);
            }
        }

        return nullptr;
    }

    int todolistUpdate(Todo * dto)
    {
        Todo *saved = todolistLoad(dto->id);
        free(saved->description);
        saved->description = malloc(sizeof(char) * strlen(dto->description));
        strcpy(saved->description, dto->description);

        return saved->id;
    }

    void todolistDelete(int id)
    {
        std::list<Todo>::iterator toDelete;
        for (std::list<Todo>::iterator item = todoListRepository.begin(); item != todoListRepository.end(); ++item)
        {
            if (item->id != id)
            {
                continue;
            }
            toDelete = item;
            break;
        }
        free(toDelete->description);
        todoListRepository.erase(toDelete);
    }
}


