#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ID_LEN 5
#define MAXLEN 50
typedef struct Audio_Book
{
   char Audio_book_id[MAX_ID_LEN];
   char Title[MAXLEN];
   char Author[MAXLEN];
   char Narrator[MAXLEN];
   float duration;
   char Genere[MAXLEN];
   float Average_rating;
   struct Audio_Book *next;
   int No_of_users_rated;

} Audio_Book;

typedef struct Audio_Book_User
{

   char Audio_book_id[MAX_ID_LEN];
   char Title[MAXLEN];
   char Author[MAXLEN];
   char Narrator[MAXLEN];
   float duration;
   char Genere[MAXLEN];
   float Average_rating;
   float rating;
   float timestamp;
   struct Audio_Book_User *next;

} Audio_Book_User;

typedef struct User_Node
{
   char User_id[MAX_ID_LEN];
   char Name[MAXLEN];
   char Email[MAXLEN];
   char Narrator_preference[MAXLEN];
   char Author_preference[MAXLEN];
   char Genere_preference[MAXLEN];
   Audio_Book_User *Audio_List;
   struct User_Node *next;

} User_Node;

Audio_Book *CreateAudio_Book(Audio_Book *a)
{
   FILE *fp = fopen("Audio_book_input.txt", "r");
   char word[MAXLEN];
   Audio_Book *tail = (Audio_Book *)malloc(sizeof(Audio_Book));
   a = tail;
   while (fscanf(fp, " %s", word) == 1)
   {
      Audio_Book *temp = (Audio_Book *)malloc(sizeof(Audio_Book));
      tail->next = temp;
      strcpy(temp->Audio_book_id, word);
      fscanf(fp, "%s", word);
      strcpy(temp->Title, word);
      fscanf(fp, "%s", word);
      strcpy(temp->Author, word);
      fscanf(fp, "%s", word);
      strcpy(temp->Narrator, word);
      float q;
      fscanf(fp, "%f", &q);
      temp->duration = q;
      fscanf(fp, "%s", word);
      strcpy(temp->Genere, word);
      fscanf(fp, "%f", &q);
      temp->Average_rating = q;
      int num;
      fscanf(fp, "%d", &num);
      temp->No_of_users_rated = num;

      temp->next = NULL;
      tail = tail->next;
   }
   tail = a;
   a = a->next;
   free(tail);
   fclose(fp);
   return a;
}

Audio_Book_User *get_Audio_List(Audio_Book *head, char arr[])
{

   Audio_Book_User *result = (Audio_Book_User *)malloc(sizeof(Audio_Book_User));
   int found = 0;
   while (head != NULL && !found)
   {

      if (strcmp(arr, head->Audio_book_id) == 0)
      {
         strcpy(result->Audio_book_id, head->Audio_book_id);
         strcpy(result->Title, head->Title);
         strcpy(result->Author, head->Author);
         strcpy(result->Narrator, head->Narrator);
         strcpy(result->Genere, head->Genere);
         result->duration = head->duration;
         result->Average_rating = head->Average_rating;
         result->rating = 0;
         result->timestamp = 0;
         found = 1;
      }
      else
      {
         head = head->next;
      }
   }
   return result;
}

User_Node *Create_User_List(User_Node *u, Audio_Book *a)
{
   char word[MAXLEN];
   FILE *fp = fopen("Users_input.txt", "r");
   User_Node *tail = (User_Node *)malloc(sizeof(User_Node));
   u = tail;
   while (fscanf(fp, "%s", word) == 1)
   {
      User_Node *temp = (User_Node *)malloc(sizeof(User_Node));
      tail->next = temp;
      temp->next = NULL;
      tail = tail->next;
      strcpy(temp->User_id, word);
      fscanf(fp, "%s", word);
      strcpy(temp->Name, word);

      fscanf(fp, "%s", word);
      strcpy(temp->Email, word);
      fscanf(fp, "%s", word);
      strcpy(temp->Narrator_preference, word);
      fscanf(fp, "%s", word);
      strcpy(temp->Author_preference, word);

      fscanf(fp, "%s", word);
      strcpy(temp->Genere_preference, word);

      Audio_Book_User *secondtail = (Audio_Book_User *)malloc(sizeof(Audio_Book_User));
      Audio_Book_User *result = secondtail;

      while ((fscanf(fp, "%s", word) == 1) && (strcmp(word, "end") != 0))
      {
         secondtail->next = get_Audio_List(a, word);
         secondtail = secondtail->next;
         secondtail->next = NULL;
      }
      Audio_Book_User *nodetodelete = result;
      result = result->next;
      temp->Audio_List = result;
      free(nodetodelete);
   }

   tail = u;
   u = u->next;
   free(tail);
   fclose(fp);

   return u;
}
void Visit_Audio_book(Audio_Book* head)
{
    printf("%s\t", head->Audio_book_id);
      printf("%s\t", head->Title);
      printf("%s\t", head->Author);
      printf("%s\t", head->Narrator);
      printf("%.2f\t", head->Average_rating);
      printf("%s\t", head->Genere);
      int hour = (int)head->duration;
      int mins = (int)((head->duration - hour) * 60);
      printf("%d:%d (HH:MM)\n", hour, mins);

   return ;
}

void print_Audio_Book(Audio_Book *head)
{
   printf("ID\t");
   printf("Title\t\t");
   printf("Author\t\t");
   printf("Narrator\t");
   printf("Avg_rating\t");
   printf("Genere\t\t");
   printf("Duration\n");
   while (head != NULL)
   {
      Visit_Audio_book(head);
     
      head = head->next;
   }
   printf("\n");
}
void Visit_Audio_Book_User(Audio_Book_User *head)
{

  
      printf("%s\t", head->Audio_book_id);
      printf("%s\t", head->Title);
      printf("%s\t", head->Author);
      printf("%s\t", head->Narrator);
      printf("%.2f\t", head->Average_rating);
      printf("%s\t", head->Genere);
      printf("%.2f\t", head->rating);
      int hour = (int)head->duration;
      int mins = (int)((head->duration - hour) * 60);
      printf("%d:%d (HH:MM)\t", hour, mins);
      hour = (int)head->timestamp;
      mins = (int)((head->timestamp - hour) * 60);
      printf("%d:%d (HH:MM)\n", hour, mins);

   return ;
}

void print_Audio_Book_User(Audio_Book_User *head)
{
   printf("ID\t");
   printf("Title\t\t");
   printf("Author\t\t");
   printf("Narrator\t");
   printf("Avg rating\t");
   printf("Genere\t");
   printf("Rating\t");
   printf("Duration\t");
   printf("Timestamp\n");
   while (head != NULL)
   {
      Visit_Audio_Book_User(head);
      head = head->next;
   }
   printf("\n");
}
void Visit_User(User_Node *u)
{
    printf("%s\t", u->User_id);
      printf("%s\t", u->Name);
      printf("%s\t", u->Email);
      printf("%s\t", u->Narrator_preference);
      printf("%s\t ", u->Genere_preference);
      printf("%s \n", u->Author_preference);
   return ;
}
void print_User_List(User_Node *u)
{
   while (u != NULL)
   {
     Visit_User(u);
      u = u->next;
   }
   printf("\n");
}

void add_AudioBook(Audio_Book **main_Audiolist, char id[], char title[], char author[], char narrator[], float duration, char genre[], float avgrating)
{
   Audio_Book *Audiolist = (*main_Audiolist);
   Audio_Book *ret_ptr = Audiolist;
   Audio_Book *ab_ptr = Audiolist;
   int isduplicate = 0;
   while (ab_ptr != NULL && isduplicate != 1)
   {
      if (strcmp(ab_ptr->Audio_book_id, id) == 0)
      {
         isduplicate = 1;
      }
      ab_ptr = ab_ptr->next;
   }
   if (isduplicate == 0)
   {
      Audio_Book *newbook = (Audio_Book *)malloc(sizeof(Audio_Book));
      strcpy(newbook->Audio_book_id, id);
      strcpy(newbook->Title, title);
      strcpy(newbook->Author, author);
      strcpy(newbook->Genere, genre);
      strcpy(newbook->Narrator, narrator);
      newbook->Average_rating = avgrating;
      newbook->duration = duration;
      newbook->No_of_users_rated = 0;
      newbook->next = NULL;
      ab_ptr = Audiolist;
      Audio_Book *ab_ptr_prev = NULL;
      int added = 0;
      if (strcmp(ab_ptr->Audio_book_id, id) > 0)
      {
         newbook->next = Audiolist;
         (*main_Audiolist) = newbook;
         added = 1;
      }
      else
      {
         while (ab_ptr != NULL && !added)
         {
            if (strcmp(ab_ptr->Audio_book_id, id) > 0)
            {
               newbook->next = ab_ptr;
               ab_ptr_prev->next = newbook;
               added = 1;
            }
            else
            {
               ab_ptr_prev = ab_ptr;
               ab_ptr = ab_ptr->next;
            }
         }
         if (ab_ptr == NULL && !added)
         {
            ab_ptr_prev->next = newbook;
            added = 1;
         }
      }
      if (added)
         printf("Successfully inserted Audiobook with ID :%s\n", newbook->Audio_book_id);
   }
   else
   {
      printf("Book is already present in Audiobook list\n");
   }
   return;
}

void Edit_AudioBook(Audio_Book Audiolist[], char id[])
{
   Audio_Book *ptr = Audiolist;
   while (ptr != NULL && strcmp(ptr->Audio_book_id, id) != 0)
   {
      ptr = ptr->next;
   }
   if (ptr == NULL)
   {
      printf("Audio Book with ID %s not found\n", id);
   }
   else
   {
      int t = 1, n;
      char *temp;
      while (t != 0)
      {
         printf("Which field you want to modify\n");
         printf("1.Title\n");
         printf("2.Author\n");
         printf("3.Duration\n");
         printf("Press 0 for exit\n");
         scanf("%d", &n);
         float d;
         switch (n)
         {
         case 1:
            printf("Enter the Title \n");
            scanf("%s", temp);
            strcpy(ptr->Title, temp);
            printf("Title of Audio Book with ID %s modified successfully\n", id);
            break;
         case 2:
            printf("Enter the Author \n");
            scanf("%s", temp);
            strcpy(ptr->Author, temp);
            printf("Author of Audio Book with ID %s modified successfully\n", id);
            break;

         case 3:
            printf("Enter the duration \n");
            scanf("%f", &d);
            ptr->duration = d;
            printf("Duration of Audio Book with ID %s modified successfully\n", id);
            break;
         case 0:
            printf("Exiting\n");
            t = 0;
            break;

         default:
            printf("Invalid input\n");
            break;
         }
      }
   }
   return;
}

void Delete_audiobook(Audio_Book *audiolist, User_Node *User_List)
{
   print_Audio_Book(audiolist);
   printf("\n");
   char temp[MAXLEN];
   printf("According to what do you want to delete ?\n");
   printf("1.Title\n");
   printf("2.Author\n");
   int n;
   int deleted = 0;
   Audio_Book *ptr = audiolist;
   Audio_Book *prev = NULL;
   scanf("%d", &n);
   if (n == 1)
   {
      printf("Enter title name:\n");
      scanf("%s", temp);
   }
   else if (n == 2)
   {
      printf("Enter author name:\n");
      scanf("%s", temp);
   }
   else
   {
      printf("Invalid input\n");
   }

   while (ptr != NULL && !deleted)
   {
      if ((n == 1 && strcmp(ptr->Title, temp) == 0) || (n == 2 && strcmp(ptr->Author, temp) == 0))
      {
         Audio_Book *del = ptr;
         if (prev == NULL)
         {
            audiolist = ptr->next;
         }
         else
         {
            prev->next = ptr->next;
         }
         printf("Audio book with ID %s is deleted from Audio list\n", del->Audio_book_id);
         del->next = NULL;
         free(del);
         deleted = 1;
      }
      prev = ptr;
      ptr = ptr->next;
   }

   User_Node *uptr = User_List;
   while (uptr != NULL)
   {
      Audio_Book_User *abu_ptr = uptr->Audio_List;
      Audio_Book_User *abu_prev = NULL;
      while (abu_ptr != NULL)
      {
         if ((n == 1 && strcmp(abu_ptr->Title, temp) == 0) || (n == 2 && strcmp(abu_ptr->Author, temp) == 0))
         {
            Audio_Book_User *del = abu_ptr;
            if (abu_prev == NULL)
            {
               uptr->Audio_List = abu_ptr->next;
            }
            else
            {
               abu_prev->next = abu_ptr->next;
            }
            printf("Audio book with ID %s is deleted from user with ID %s\n", del->Audio_book_id, uptr->User_id);
            del->next = NULL;
            free(del);
            deleted = 1;
         }
         abu_prev = abu_ptr;
         abu_ptr = abu_ptr->next;
      }
      uptr = uptr->next;
   }
   if (n == 1 && !deleted)
      printf("Audio book with title %s not found\n", temp);
   else if (n == 2 && !deleted)
      printf("Audio book with author %s not found\n", temp);
   print_Audio_Book(audiolist);
}

void Search_Audio_Book(Audio_Book *head)
{
   printf("According to what do you want to search ?\n");
   printf("1.Title\n");
   printf("2.Author\n");
   printf("3.Genere\n");

   int t = 1;
   Audio_Book *Audiolist = head;

   int n;
   char str[MAXLEN];
   scanf("%d", &n);
   if (n == 1)
   {
      printf("Enter the Title\n");
      scanf("%s", str);
   }
   else if (n == 2)
   {
      printf("Enter the Author\n");
      scanf("%s", str);
   }
   else if (n == 3)
   {
      printf("Enter the Genre\n");
      scanf("%s", str);
   }
   int found = 0;

   while (Audiolist != NULL)
   {
      if ((n == 1 && strcmp(Audiolist->Title, str) == 0) || (n == 2 && strcmp(Audiolist->Author, str) == 0) || (n == 3 && strcmp(Audiolist->Genere, str) == 0))
      {
         found = 1;
         printf("The audio book ID is %s\n", Audiolist->Audio_book_id);
      }
      Audiolist = Audiolist->next;
   }
   if (n == 1 && !found)
      printf("Audio book with title %s not found\n", str);
   else if (n == 2 && !found)
      printf("Audio book with author %s not found\n", str);
   else if (n == 3 && !found)
      printf("Audio book with genre %s not found\n", str);

   return;
}

void Add_User_profile(User_Node **Mainhead)
{
   User_Node *User_head = (*Mainhead);
   char word[MAXLEN];
   char id[MAXLEN];
   printf("Enter the email for the user :");
   scanf("%s", word);
   printf("Enter user id :");
   scanf("%s", id);
   int flag = 0;
   User_Node *temp = User_head;
   while (temp != NULL && !flag)
   {
      if (strcmp(temp->Email, word) == 0)
      {
         printf("The email : %s already exist \n", word);
         flag = 1;
      }
      else if (strcmp(temp->User_id, id) == 0)
      {
         printf("The user ID : %s already exist \n", id);
         flag = 1;
      }
      else
      {
         temp = temp->next;
      }
   }
   if (!flag)
   {
      User_Node *New_user = (User_Node *)malloc(sizeof(User_Node));
      strcpy(New_user->Email, word);
      strcpy(New_user->User_id, id);
      printf("Enter user name :");
      scanf("%s", word);
      strcpy(New_user->Name, word);
      printf("Enter user genere_preference :");
      scanf("%s", word);
      strcpy(New_user->Genere_preference, word);
      printf("Enter user narrator_preference :");
      scanf("%s", word);
      strcpy(New_user->Narrator_preference, word);
      printf("Enter user author_preference :");
      scanf("%s", word);
      strcpy(New_user->Author_preference, word);

      New_user->next = NULL;
      int done = 0;
      temp = User_head;
      User_Node *prev = NULL;
      while (!done && temp != NULL)
      {
         if (strcmp(New_user->User_id, temp->User_id) < 0)
         {
            if (prev == NULL)
            {
               New_user->next = User_head;
               (*Mainhead) = New_user;
            }
            else
            {

               New_user->next = temp;
               prev->next = New_user;
            }
            done = 1;
         }
         else
         {
            prev = temp;
            temp = temp->next;
         }
      }
      if (done == 0)
      {
         prev->next = New_user;
      }
      printf("User account created successfully\n");
   }
   return;
}

void add_audio_book_to_user(Audio_Book_User **main_head, Audio_Book *AB)
{
   Audio_Book_User *head = (*main_head);
   char word[MAXLEN];
   printf("Enter the audio book ID : ");
   scanf("%s", word);
   int found = 0;
   while (!found && AB != NULL)
   {

      if (strcmp(word, AB->Audio_book_id) == 0)
      {
         found = 1;
      }
      else
      {
         AB = AB->next;
      }
   }
   if (found == 0)
   {

      printf("The audio book with ID %s is not available \n ", word);
   }

   else
   {
      Audio_Book_User *temp = head;
      found = 0;
      while (temp != NULL && !found)
      {
         if (strcmp(temp->Audio_book_id, word) == 0)
         {
            printf("The audio book with ID %s is already present in this user library\n", word);
            found = 1;
         }
         else
         {
            temp = temp->next;
         }
      }

      if (found == 0)
      {
         Audio_Book_User *new_book = (Audio_Book_User *)malloc(sizeof(Audio_Book_User));

         strcpy(new_book->Audio_book_id, AB->Audio_book_id);
         strcpy(new_book->Author, AB->Author);
         strcpy(new_book->Title, AB->Title);
         strcpy(new_book->Narrator, AB->Narrator);
         strcpy(new_book->Genere, AB->Genere);
         new_book->Average_rating = AB->Average_rating;
         new_book->duration = AB->duration;
         new_book->timestamp = 0.0;
         new_book->rating = 0.0;
         // new_book->next = NULL;
         if (head == NULL)
         {
            (*main_head) = new_book;
         }
         else
         {
            Audio_Book_User *prev = NULL;
            while ((head != NULL) && strcmp(head->Audio_book_id, new_book->Audio_book_id) < 0)
            {
               prev = head;
               head = head->next;
            }
            if (prev == NULL)
            {
               new_book->next = head;
               (*main_head) = new_book;
            }
            else
            {
               new_book->next = head;
               prev->next = new_book;
            }
         }
         printf("Audio book with ID %s added successfully\n", new_book->Audio_book_id);
      }
   }
   return;
}

void delete_audio_book_from_user(Audio_Book_User **main_head)
{
   Audio_Book_User *head = (*main_head);
   char word[MAXLEN];
   printf("Enter the ID of audio book you want to delete\n");
   scanf("%s", word);
   Audio_Book_User *prev = NULL;
   int found = 0;
   while (head != NULL && !found)
   {
      if (strcmp(head->Audio_book_id, word) == 0)
      {
         found = 1;
         Audio_Book_User *nodetodelete = head;
         if (prev == NULL)
         {
            head = head->next;
            (*main_head) = head;
         }
         else
         {
            prev->next = head->next;
         }
         free(nodetodelete);
      }
      else
      {
         prev = head;
         head = head->next;
      }
   }
   if (found == 0)
   {
      printf("The audio book with ID %s is not available in this user library\n ", word);
   }
   else
   {
      printf("Audio book deleted successfully\n");
   }

   return;
}

void Add_to_User_Library(User_Node *head, Audio_Book *Audio_Book)
{

   printf("Enter user ID you want to add/delete audiobooks :");
   char word[MAXLEN];
   scanf("%s", word);
   int found = 0;
   while (head != NULL && !found)
   {
      if (strcmp(head->User_id, word) == 0)
      {
         found = 1;
      }
      else
      {
         head = head->next;
      }
   }
   if (found == 0)
   {
      printf("User not found\n");
   }
   else
   {
      int t = 1;
      while (t != 0)
      {
         printf("Enter what opreation you want to perfrom\n");
         printf("0.Exit\n");
         printf("1.Add audiobook\n");
         printf("2.Delete audiobook\n");
         int c;
         scanf("%d", &c);
         switch (c)
         {
         case 0:
            t = 0;
            break;
         case 1:
            add_audio_book_to_user((&head->Audio_List), Audio_Book);
            break;
         case 2:
            delete_audio_book_from_user((&head->Audio_List));
            break;

         default:
            printf("Invalid input\n");
            break;
         }
      }
   }

   return;
}

void Listening_Progress(char UserId[], char AudioBook_id[], float listened_time, User_Node *user_head)
{

   int found = 0;
   User_Node *temp = user_head;
   while (!found && temp != NULL)
   {
      if (strcmp(UserId, temp->User_id) == 0)
      {
         found = 1;
         int flag = 0;
         Audio_Book_User *traversal = temp->Audio_List;
         while (!flag && traversal != NULL)
         {
            if (strcmp(traversal->Audio_book_id, AudioBook_id) == 0)
            {

               flag = 1;
               traversal->timestamp += listened_time;
            }
            else
            {
               traversal = traversal->next;
            }
         }
         if (flag == 0)
         {
            printf("The user with ID %s dont have the given Audio book with ID %s \n", UserId, AudioBook_id);
         }
         else
         {
            printf("Listening progress is added successfully\n ");
         }
      }
      else
      {
         temp = temp->next;
      }
   }
   if (found == 0)
   {
      printf(" The user with %s ID not found \n ", UserId);
   }

   return;
}

Audio_Book_User *divide_abu(Audio_Book_User *head)
{
   Audio_Book_User *slow = head;
   Audio_Book_User *fast = head->next;
   while (fast != NULL && fast->next != NULL)
   {
      fast = fast->next;
      slow = slow->next;

      fast = fast->next;
   }
   Audio_Book_User *ptr = slow->next;
   slow->next = NULL;

   return ptr;
}

Audio_Book_User *merge_abu(Audio_Book_User *first, Audio_Book_User *second)
{
   if (first == NULL)
   {
      return second;
   }
   else if (second == NULL)
   {
      return first;
   }
   Audio_Book_User *result;
   if (first->timestamp < second->timestamp)
   {
      result = first;
      first = first->next;
   }
   else
   {
      result = second;
      second = second->next;
   }
   Audio_Book_User *tail = result;
   while (first != NULL && second != NULL)
   {
      if (first->timestamp < second->timestamp)
      {
         tail->next = first;
         first = first->next;
         tail = tail->next;
      }
      else
      {
         tail->next = second;
         second = second->next;
         tail = tail->next;
      }
   }
   if (first != NULL)
   {

      tail->next = first;
   }
   else
   {
      tail->next = second;
   }

   return result;
}

Audio_Book_User *mergesort_abu_listeningtime(Audio_Book_User *lptr)
{

   Audio_Book_User *head = lptr;
   if (lptr != NULL && lptr->next != NULL)
   {
      Audio_Book_User *middle = divide_abu(lptr);
      middle = mergesort_abu_listeningtime(middle);
      lptr = mergesort_abu_listeningtime(lptr);
      head = merge_abu(lptr, middle);
   }
   return head;
}

Audio_Book_User *merge_abu_id(Audio_Book_User *first, Audio_Book_User *second)
{
   if (first == NULL)
   {
      return second;
   }
   else if (second == NULL)
   {
      return first;
   }
   Audio_Book_User *result;
   if (strcmp(first->Audio_book_id, second->Audio_book_id) < 0)
   {
      result = first;
      first = first->next;
   }
   else
   {
      result = second;
      second = second->next;
   }
   Audio_Book_User *tail = result;
   while (first != NULL && second != NULL)
   {
      if (strcmp(first->Audio_book_id, second->Audio_book_id) < 0)
      {
         tail->next = first;
         first = first->next;
         tail = tail->next;
      }
      else
      {
         tail->next = second;
         second = second->next;
         tail = tail->next;
      }
   }
   if (first != NULL)
   {

      tail->next = first;
   }
   else
   {
      tail->next = second;
   }

   return result;
}

Audio_Book_User *mergesort_abu_user_id(Audio_Book_User *lptr)
{
   Audio_Book_User *head = lptr;
   if (lptr != NULL && lptr->next != NULL)
   {
      Audio_Book_User *middle = divide_abu(lptr);
      middle = mergesort_abu_user_id(middle);
      lptr = mergesort_abu_user_id(lptr);
      head = merge_abu_id(lptr, middle);
   }
   return head;
}

Audio_Book_User *reverse_abu(Audio_Book_User *head)
{
   Audio_Book_User *curr = head;
   Audio_Book_User *prev = NULL;
   Audio_Book_User *nextn = NULL;
   while (curr != NULL)
   {
      nextn = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextn;
   }

   return prev;
}

void Display_User_Libraries(char User_ID[], User_Node *head)
{
   User_Node *temp2 = head;
   int found = 0;
   while (temp2 != NULL && !found)
   {
      if (strcmp(User_ID, temp2->User_id) == 0)
      {
         found = 1;
      }
      else
      {
         temp2 = temp2->next;
      }
   }
   if (found == 0)
   {
      printf("The user with user_id %s is not found\n", User_ID);
   }
   else
   {
      printf("Enter the Operation number to be performed\n");
      printf("1.Display all audiobooks\n");
      printf("2.Display audiobooks by genre\n");
      printf("3.Display audiobooks by title\n");
      int n;
      scanf("%d", &n);
      char str[MAXLEN];

      Audio_Book_User *temp = temp2->Audio_List;
      temp = mergesort_abu_listeningtime(temp);
      temp = reverse_abu(temp);

      if (n == 1)
      {
         while (temp != NULL)
         {

            printf("Audio Book with ID : %s\n", temp->Audio_book_id);
            temp = temp->next;
         }
      }
      else if (n == 2)
      {
         printf("Enter Genere name:\n");
         scanf("%s", str);
         int f2 = 0;
         while (temp != NULL)
         {
            if (strcmp(temp->Genere, str) == 0)
            {
               printf("%s with Audio Book ID : %s\n", temp->Genere, temp->Audio_book_id);
               f2 = 1;
            }

            temp = temp->next;
         }
         if (!f2)
            printf("Audiobook with Genre %s not found\n", str);
      }
      else if (n == 3)
      {
         printf("Enter Title:\n");
         scanf("%s", str);
         int f1 = 0;
         while (temp != NULL)
         {
            if (strcmp(temp->Title, str) == 0)
            {
               printf("%s with Audio Book ID : %s\n", temp->Title, temp->Audio_book_id);
               f1 = 1;
            }

            temp = temp->next;
         }
         if (!f1)
            printf("Audiobook with Title %s not found\n", str);
      }
      else
      {
         printf("Invalid input\n");
      }
      temp = mergesort_abu_user_id(temp);
   }

   return;
}

void set_Average_rating(Audio_Book *AB, User_Node *UN, float avgrating, char id[])
{
   // changing average rating in case of audio books
   while (AB != NULL)
   {
      if (strcmp(AB->Audio_book_id, id) == 0)
      {
         AB->Average_rating = avgrating;
      }
      AB = AB->next;
   }
   // changing the average rating in users
   while (UN != NULL)
   {
      Audio_Book_User *temp = UN->Audio_List;
      while (temp != NULL)
      {
         if (strcmp(temp->Audio_book_id, id) == 0)
         {
            temp->Average_rating = avgrating;
         }
         temp = temp->next;
      }
      UN = UN->next;
   }

   return;
}

void Rate_Audio_Book(char UserId[], char AudioBook_id[], float user_rating, User_Node *user_head, Audio_Book *AB)
{
   if (user_rating >= 0.0 && user_rating <= 5.0)
   {
      int user_found = 0;
      User_Node *temp = user_head;
      while (!user_found && temp != NULL)
      {
         if (strcmp(UserId, temp->User_id) == 0)
         {
            user_found = 1;
            int audio_book_found = 0;
            Audio_Book_User *traversal = temp->Audio_List;
            while (!audio_book_found && traversal != NULL)
            {

               if (strcmp(traversal->Audio_book_id, AudioBook_id) == 0)
               {
                  audio_book_found = 1;

                  if (traversal->timestamp == 0.0)
                  {
                     printf("You haven't Listened the song you are not allowed to rate the Audio book\n");
                  }
                  else
                  {

                     Audio_Book *Ah = AB;
                     int noofusers;
                     int done = 0;
                     while (Ah != NULL && !done)
                     {

                        if (strcmp(Ah->Audio_book_id, AudioBook_id) == 0)
                        {
                           noofusers = Ah->No_of_users_rated;
                           if (traversal->rating == 0.0)
                           {

                              Ah->No_of_users_rated += 1;
                           }
                           done = 1;
                        }
                        Ah = Ah->next;
                     }
                     traversal->Average_rating = ((traversal->Average_rating) * noofusers) - traversal->rating + user_rating;
                     if (traversal->rating == 0.0)
                     {
                        noofusers++;
                     }
                     traversal->Average_rating = (traversal->Average_rating) / noofusers;
                     traversal->rating = user_rating;
                     set_Average_rating(AB, user_head, traversal->Average_rating, AudioBook_id);
                  }
               }
               else
               {
                  traversal = traversal->next;
               }
            }
            if (audio_book_found == 0)
            {
               printf("The user with ID %s don't have the given audio book with ID %s\n", UserId, AudioBook_id);
            }
            else
            {
               printf("Rating is added successfully\n");
            }
         }
         else
         {
            temp = temp->next;
         }
      }
      if (user_found == 0)
      {
         printf("The user with ID %s  not found\n", UserId);
      }
   }
   else
   {
      printf("Enter rating from 0-5 only\n");
   }

   return;
}

void Most_poplular_audiobook(Audio_Book *audiolist)
{
   float most_popular = 0.0;
   float curr = 0.0;
   int non_zero_rating = 0;
   Audio_Book *ab_ptr = audiolist;
   Audio_Book *mostpopular_ab;
   while (ab_ptr != NULL)
   {
      curr = ab_ptr->Average_rating;
      if (most_popular < curr)
      {
         most_popular = curr;
         mostpopular_ab = ab_ptr;
      }
      if (ab_ptr->Average_rating > 0.0)
      {
         non_zero_rating = 1;
      }
      ab_ptr = ab_ptr->next;
   }

   if (!non_zero_rating)
   {
      printf("No ratings are available to determine popularity.\n");
   }
   else
   {
      ab_ptr = audiolist;
      while (ab_ptr != NULL)
      {
         if (ab_ptr->Average_rating == mostpopular_ab->Average_rating)
         {
            printf("\nDetails of most popular audiobook are\n");
            printf("Title %s\n", mostpopular_ab->Title);
            printf("Author %s\n", mostpopular_ab->Author);
            printf("Avg rating %f\n", mostpopular_ab->Average_rating);
         }
         ab_ptr = ab_ptr->next;
      }
   }

   return;
}

void Listening_history_report_user(User_Node *User_List, char *userid)
{
   User_Node *ptr = User_List;
   int user_found = 0;
   while (ptr != NULL && !user_found)
   {
      if (strcmp(ptr->User_id, userid) == 0)
         user_found = 1;
      else
         ptr = ptr->next;
   }
   if (ptr == NULL && !user_found)
   {
      printf("User not found\n");
   }
   else
   {
      Audio_Book_User *abptr = ptr->Audio_List;
      printf("Title\t\t");
      printf("Author\t\t");
      printf("Total Time\t\t\n");
      float total_lis_time = 0.0;

      while (abptr != NULL)
      {
         if (abptr->timestamp > 0)
         {
            printf("%s\t\t", abptr->Title);
            printf("%s\t\t", abptr->Author);
            printf("%.2f\t\t", abptr->timestamp);
            total_lis_time += abptr->timestamp;
            printf("\n");
         }
         abptr = abptr->next;
      }
      printf("\nTotal listening time of user with ID %s is %.2f", userid, total_lis_time);
   }
}

Audio_Book_User *merge(Audio_Book_User *ab1, Audio_Book_User *ab2)
{
   Audio_Book_User *ptr1, *ptr2, *result, *tail;

   if (ab1 == NULL)
      return ab2;
   else if (ab2 == NULL)
      return ab1;
   ptr1 = ab1;
   ptr2 = ab2;

   if (strcmp(ab1->Title, ab2->Title) < 0 || (strcmp(ab1->Title, ab2->Title) == 0 && strcmp(ab1->Author, ab2->Author) < 0))
   {
      result = ab1;
      ptr1 = ptr1->next;
   }
   else
   {
      result = ab2;
      ptr2 = ptr2->next;
   }
   tail = result;

   while (ptr1 != NULL && ptr2 != NULL)
   {
      if (strcmp(ptr1->Title, ptr2->Title) < 0 || (strcmp(ptr1->Title, ptr2->Title) == 0 && strcmp(ptr1->Author, ptr2->Author) < 0))
      {
         tail->next = ptr1;
         tail = tail->next;
         ptr1 = ptr1->next;
      }
      else if (strcmp(ptr1->Title, ptr2->Title) > 0 || (strcmp(ptr1->Title, ptr2->Title) == 0 && strcmp(ptr1->Author, ptr2->Author) > 0))
      {
         tail->next = ptr2;
         tail = tail->next;
         ptr2 = ptr2->next;
      }
   }

   if (ptr1 != NULL)
      tail->next = ptr1;
   else
      tail->next = ptr2;

   return result;
}

Audio_Book_User *mergesort(Audio_Book_User *ab_user)
{
   Audio_Book_User *ab_ptr;
   Audio_Book_User *head = ab_user;

   if (ab_user != NULL && ab_user->next != NULL)
   {
      ab_ptr = divide_abu(ab_user);
      ab_user = mergesort(ab_user);
      ab_ptr = mergesort(ab_ptr);
      head = merge(ab_user, ab_ptr);
   }
   return head;
}

Audio_Book_User *CreateNewAudioBook_User(Audio_Book_User *abu)
{

   Audio_Book_User *newbook = (Audio_Book_User *)malloc(sizeof(Audio_Book_User));
   strcpy(newbook->Audio_book_id, abu->Audio_book_id);
   strcpy(newbook->Author, abu->Author);
   strcpy(newbook->Genere, abu->Genere);
   strcpy(newbook->Narrator, abu->Narrator);
   strcpy(newbook->Title, abu->Title);
   newbook->next = NULL;
   newbook->duration = abu->duration;
   newbook->Average_rating = abu->Average_rating;
   newbook->rating = 0.0;
   newbook->timestamp = 0.0;

   return newbook;
}

void Merge_user_libraries(User_Node *userlist, char id1[], char id2[])
{
   User_Node *user1 = userlist;
   User_Node *user2 = userlist;
   int found = 0;
   int user1found = 0;
   int user2found = 0;

   if (strcmp(id1, id2) == 0)
      printf("Same user IDs\n");
   else
   {

      while (user1 != NULL && user2 != NULL && found != 2)
      {
         if (strcmp(user1->User_id, id1) == 0 && !user1found)
         {
            found += 1;
            user1found = 1;
         }
         else if (strcmp(user2->User_id, id2) == 0 && !user2found)
         {
            found += 1;
            user2found = 1;
         }
         if (!user1found)
            user1 = user1->next;
         if (!user2found)
            user2 = user2->next;
      }
   }

   if (found != 2)
      printf("Both users not found\n");
   else
   {

      Audio_Book_User *ab_ptr1 = user1->Audio_List;
      Audio_Book_User *ab_ptr2 = user2->Audio_List;
      Audio_Book_User *result1 = (Audio_Book_User *)malloc(sizeof(Audio_Book_User));
      Audio_Book_User *result2 = (Audio_Book_User *)malloc(sizeof(Audio_Book_User));
      Audio_Book_User *ab_tail1 = result1;
      Audio_Book_User *ab_tail2 = result2;
      result1->next = ab_ptr1;
      result2->next = ab_ptr2;
      while (ab_ptr1 != NULL && ab_ptr2 != NULL)
      {
         if (strcmp(ab_ptr1->Audio_book_id, ab_ptr2->Audio_book_id) < 0)
         {
            Audio_Book_User *newbook = CreateNewAudioBook_User(ab_ptr1);
            newbook->next = ab_ptr2;
            ab_tail2->next = newbook;
            ab_ptr1 = ab_ptr1->next;
         }
         else if (strcmp(ab_ptr1->Audio_book_id, ab_ptr2->Audio_book_id) > 0)
         {
            Audio_Book_User *newbook = CreateNewAudioBook_User(ab_ptr2);
            newbook->next = ab_ptr1;
            ab_tail1->next = newbook;
            ab_ptr2 = ab_ptr2->next;
         }
         else
         {
            ab_ptr1 = ab_ptr1->next;
            ab_ptr2 = ab_ptr2->next;
         }
         ab_tail2 = ab_tail2->next;
         ab_tail1 = ab_tail1->next;
      }
      if (ab_ptr1 == NULL)
      {
         while (ab_ptr2 != NULL)
         {
            Audio_Book_User *newbook = CreateNewAudioBook_User(ab_ptr2);
            ab_tail1->next = newbook;
            ab_tail1 = ab_tail1->next;
            ab_ptr2 = ab_ptr2->next;
         }
      }
      else if (ab_ptr2 == NULL)
      {
         while (ab_ptr1 != NULL)
         {
            Audio_Book_User *newbook = CreateNewAudioBook_User(ab_ptr1);
            ab_tail2->next = newbook;
            ab_tail2 = ab_tail2->next;
            ab_ptr1 = ab_ptr1->next;
         }
      }
      ab_tail1 = result1;
      result1 = result1->next;
      free(ab_tail1);
      ab_tail2 = result2;
      result2 = result2->next;
      free(ab_tail2);
      user1->Audio_List = mergesort(result1);
      user2->Audio_List = mergesort(result2);

      printf("User libraries of users with IDs %s and %s are merged successfully\n", id1, id2);
   }
   return;
}

void Listening_history_report_audiobook(User_Node *userlist, Audio_Book *audiolist, char id[])
{
   Audio_Book *a_ptr = audiolist;
   while (a_ptr != NULL && strcmp(a_ptr->Audio_book_id, id) != 0)
      a_ptr = a_ptr->next;
   if (a_ptr == NULL)
      printf("Audio Book with ID %s not found\n", id);
   else
   {
      User_Node *u_ptr = userlist;
      int userfound = 0;
      float total_listening_time = 0;
      while (u_ptr != NULL)
      {
         Audio_Book_User *abu_ptr = u_ptr->Audio_List;
         while (abu_ptr != NULL)
         {
            if (strcmp(abu_ptr->Audio_book_id, id) == 0)
            {
               total_listening_time += abu_ptr->timestamp;
               userfound = 1;
            }
            abu_ptr = abu_ptr->next;
         }
         u_ptr = u_ptr->next;
      }
      if (userfound)
      {
         printf("ID :%s\n", a_ptr->Audio_book_id);
         printf("Title :%s\n", a_ptr->Title);
         printf("Author :%s\n", a_ptr->Author);
         printf("Total listening time :%.2f\n", total_listening_time);
      }
      else
         printf("User not found with AudioBook ID :%s", id);
   }
}

Audio_Book *divide_ab(Audio_Book *head)
{
   Audio_Book *slow = head;
   Audio_Book *fast = head->next;
   while (fast != NULL && fast->next != NULL)
   {
      fast = fast->next->next;
      slow = slow->next;
   }
   Audio_Book *ptr = slow->next;
   slow->next = NULL;

   return ptr;
}

Audio_Book *merge_ab(Audio_Book *first, Audio_Book *second)
{
   if (first == NULL)
   {
      return second;
   }
   else if (second == NULL)
   {
      return first;
   }
   Audio_Book *result;
   if (first->Average_rating < second->Average_rating)
   {
      result = first;
      first = first->next;
   }
   else
   {
      result = second;
      second = second->next;
   }
   Audio_Book *tail = result;
   while (first != NULL && second != NULL)
   {
      if (first->Average_rating < second->Average_rating)
      {
         tail->next = first;
         first = first->next;
         tail = tail->next;
      }
      else
      {
         tail->next = second;
         second = second->next;
         tail = tail->next;
      }
   }
   if (first != NULL)
   {

      tail->next = first;
   }
   else
   {
      tail->next = second;
   }

   return result;
}

Audio_Book *mergesort_averagerating(Audio_Book *lptr)
{
   Audio_Book *head = lptr;
   if (lptr != NULL && lptr->next != NULL)
   {
      Audio_Book *middle = divide_ab(lptr);
      middle = mergesort_averagerating(middle);
      lptr = mergesort_averagerating(lptr);
      head = merge_ab(lptr, middle);
   }
   return head;
}

Audio_Book *merge_id_ab(Audio_Book *first, Audio_Book *second)
{
   Audio_Book *result;

   if (strcmp(first->Audio_book_id, second->Audio_book_id) < 0)
   {
      result = first;
      first = first->next;
   }
   else
   {
      result = second;
      second = second->next;
   }
   Audio_Book *tail = result;
   while (first != NULL && second != NULL)
   {
      if (strcmp(first->Audio_book_id, second->Audio_book_id) < 0)
      {
         tail->next = first;
         first = first->next;
         tail = tail->next;
      }
      else
      {
         tail->next = second;
         second = second->next;
         tail = tail->next;
      }
   }
   if (first != NULL)
   {

      tail->next = first;
   }
   else
   {
      tail->next = second;
   }

   return result;
}

Audio_Book *mergesort_id_ab(Audio_Book *head)
{
   if (head != NULL && head->next != NULL)
   {
      Audio_Book *lptr = divide_ab(head);
      head = mergesort_id_ab(head);
      lptr = mergesort_id_ab(lptr);
      head = merge_id_ab(lptr, head);
   }
   return head;
}

void Display_AudioBook_List_in_sorted_order_of_Averagerating(Audio_Book **head)
{

   Audio_Book *traversal = (*head);
   // merge sort
   traversal = mergesort_averagerating(traversal);
   (*head) = traversal;
   // display of Audio_book
   printf("The names of audiobooks sorted according to the average rating are : \n ");
   while (traversal != NULL)
   {
      printf("%s\n", traversal->Title);
      traversal = traversal->next;
   }
   traversal = (*head);
   traversal = mergesort_id_ab(traversal);
   (*head) = traversal;
   return;
}

void Create_output_file(Audio_Book *Audiolist, User_Node *User_List)
{
   FILE *fp = fopen("Audio_book_input.txt", "w");
   Audio_Book *abptr = Audiolist;
   while (abptr != NULL)
   {
      fprintf(fp, "%s\t", abptr->Audio_book_id);
      fprintf(fp, "%s\t", abptr->Title);
      fprintf(fp, "%s\t", abptr->Author);
      fprintf(fp, "%s\t", abptr->Narrator);
      fprintf(fp, "%.2f\t", abptr->duration);
      fprintf(fp, "%s\t", abptr->Genere);

      fprintf(fp, "%.2f\t", abptr->Average_rating);
      fprintf(fp, "%d\n", abptr->No_of_users_rated);
      abptr = abptr->next;
   }
   fclose(fp);

   FILE *fp2 = fopen("Users_input.txt", "w");
   User_Node *u_ptr = User_List;
   while (u_ptr != NULL)
   {
      fprintf(fp2, "%s\t", u_ptr->User_id);
      fprintf(fp2, "%s\t", u_ptr->Name);
      fprintf(fp2, "%s\t", u_ptr->Email);

      fprintf(fp2, "%s\t", u_ptr->Narrator_preference);
      fprintf(fp2, "%s\t", u_ptr->Author_preference);

      fprintf(fp2, "%s\t", u_ptr->Genere_preference);
      Audio_Book_User *temp = u_ptr->Audio_List;
      while (temp != NULL)
      {
         fprintf(fp2, "%s\t", temp->Audio_book_id);
         temp = temp->next;
      }
      fprintf(fp2, "end\n");
      u_ptr = u_ptr->next;
   }
   fclose(fp2);


//   FILE* fpc;
//  FILE* fpc2;
//  fpc=fopen("audiobook_output.txt","r");
//  fpc2=fopen("Audio_book_input.txt","w");
//  if(fpc!=NULL)
//  {
//      char ch=fgetc(fpc);
//      while(ch!=EOF)
//      {
//        fputc(ch,fpc2);
//        ch=fgetc(fpc);
//      }
//  }
//  fclose(fpc);
//    fclose(fpc2);
   
//  fpc=fopen("user_output.txt","r");
//  fpc2=fopen("Users_input.txt","w");
//  if(fpc!=NULL)
//  {
//      char ch=fgetc(fpc);
//      while(ch!=EOF)
//      {
//        fputc(ch,fpc2);
//        ch=fgetc(fpc);
//      }
//  }
//  fclose(fpc);
//    fclose(fpc2);

   

   return;
}

int main()
{

   Audio_Book *Audiolist = CreateAudio_Book(NULL);
   User_Node *User_List = Create_User_List(NULL, Audiolist);
   // various functions that can be executed with the help of this system
   // print_User_List(User_List);
 //  add_AudioBook(&Audiolist, "12", "Title", "Author", "Narrator", 4.5, "Genre", 4.0);
   //print_Audio_Book(Audiolist);
  // Edit_AudioBook(Audiolist,"01");
   // Delete_audiobook(Audiolist,User_List);
   // Search_Audio_Book(Audiolist);
  //  Add_User_profile(&User_List);
   // Add_to_User_Library(User_List,Audiolist);
   // delete_audio_book_from_user()
   // Listening_Progress("05","02",23.0,User_List);
   // Display_User_Libraries("02",User_List);
   // Rate_Audio_Book("05","02",0.1,User_List,Audiolist);
   // Most_poplular_audiobook(Audiolist);
   // Listening_history_report_user(User_List,"01");
   // Merge_user_libraries(User_List, "01", "02");
   // Listening_history_report_audiobook(User_List,Audiolist,"01");
   // Display_AudioBook_List_in_sorted_order_of_Averagerating(&Audiolist);
   Create_output_file(Audiolist, User_List);

   return 0;
}
