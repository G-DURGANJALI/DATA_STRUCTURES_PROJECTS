#include "Audiobook_Avl.h"
int main()
{
    Audio_book_Tree *Audio_list = create_audiobook_tree();

    User_Tree *Users_list = create_user_tree(Audio_list);
              /*   Welcome to LIBRARY       */
    printf(" We have the  following Functions available with us\n ");
    printf("1.Add Audio Book to  Library\n");
    printf("2.Edit Audio Book  in the  Library\n");
    printf("3.Delete Audio Book from Library\n");
    printf("4.Add Audio Book to User  Library\n");
    printf("5.Add User \n");
    printf("6.Search Audio Book in the Library\n");
    printf("7.Display Listening Progress of User\n");
    printf("8.Display User Library\n");
    printf("9.Allow Users to Rate Audio Book\n");
    printf("10. Display Most Popular Audio Book\n");
    printf("11.Display User History \n");
    printf("12.Display Audio Book Listenig time\n");
    printf("13.Range search\n");
    int n;

    int t = 1;
    while (t != 0)
    {
        printf("Enter the option you Want \n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            add_AudioBook(&Audio_list);
        case 2:
            Edit_audiobook(&Audio_list);
        case 3:
            Delete_Audio_book(&Audio_list);
        case 4:
            Add_to_User_library(&Users_list, &Audio_list);
        case 5:
            add_user_profile(&Users_list);
        case 6:
            Search_audiobook(&Audio_list);
        case 7:
            Listening_progress(&Users_list, &Audio_list);
        case 8:
            Display_user_libraries(&Users_list);
        case 9:
            Rate_Audiobook(&Users_list, &Audio_list);
        case 10:
            Most_Popular_Audio_book(&Audio_list);
        case 11:
            Listening_History_report_User(&Users_list);
        case 12:
            Listening_History_Audio_book(&Audio_list, &Users_list);
        case 13:
            Modify_Users_tree_output(Users_list);
        Default:
            printf("Please choose one of the option");
        }
        printf("If you want to Exit enter 0 \n");
        scanf("%d", &t);
    }
    printf(" Exitting...\n");
 
    Modify_audiobook_tree_ouput(Audio_list);
    Modify_Users_tree_output(Users_list);

    return 0;
}
