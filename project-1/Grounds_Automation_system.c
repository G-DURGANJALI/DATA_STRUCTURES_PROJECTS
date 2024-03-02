#include <stdio.h>
#include <string.h>
#define numofgrounds 6
#define numofgames 5
#define numofdates 3
// structur definition for available dates
typedef struct availabledates
{

  char avdate[15];
  char avstarttime[15];
  char avendtime[15];

} adates;
// structur definition for scheduled dates
typedef struct scheduleddates
{
  char scdate[15];
  char scstarttime[15];
  char scendtime[15];

} sdate;
// structure definition for a game
typedef struct games
{
  char gamename[30];
  int hourlygamerate;  
  sdate d[4];       // each game is given maximum of four scheduled dates

  adates ad[4];     // each game is given maximum of four available  dates

} games;
// structur definition for a ground
struct ground
{
  char groundname[50];
  char city[30];
  char state[40];
  games g[5];           // each groundis given maximum of five games
};
// function to find the scheduled games at the given city in the given time
void getFixturesinCity(struct ground grounds[], char cityv[], char datev[], char startt[], char endt[])
{
  int flag = 0;    

  for (int i = 0; i < numofgrounds; i++)
  {
    if (strcmp(grounds[i].city, cityv) == 0)   //comparision of two city names
    {
      for (int j = 0; j < numofgames; j++)    
      {
        for (int k = 0; k < numofdates; k++)
        {
          if ((strcmp(grounds[i].g[j].d[k].scdate, datev)) == 0)    //comparision of dates
          {
            if (strcmp(grounds[i].g[j].d[k].scstarttime, startt) <= 0)   //comparision of starting time
            {
              if (strcmp(grounds[i].g[j].d[k].scendtime, endt) >= 0)    //comparision of ending time
              {
                printf("\n ground : %s,game name : %s", grounds[i].groundname, grounds[i].g[j].gamename);
                flag = 1;
              }
            }
          }
        }
      }
    }
  }

  if (flag > 0)
  {
    printf("\n these are the  games scheduled in %s city starting at %s end at %s  ", cityv, startt, endt);
  }
  else
    printf("no  games scheduled in %s city stating at %s end at %s  ", cityv, startt, endt);
  return;
}
// function to display  the names of grounds sorted based on the dates and time
void getFixtureSortedOnDate(struct ground grounds[])
{

  for (int i = 0; i < numofgrounds; i++)
  {
    for (int j = 0; j < numofgames; j++)
    {
      for (int k = 0; k < numofdates; k++)
      {
        if (strcmp(grounds[i].g[0].d[0].scdate, grounds[i].g[j].d[k].scdate) > 0)
        {

          strcpy(grounds[i].g[0].d[0].scdate, grounds[i].g[j].d[k].scdate);         // finding the minimum date string 
          strcpy(grounds[i].g[0].d[0].scstarttime, grounds[i].g[j].d[k].scstarttime);
        }
        else if (strcmp(grounds[i].g[0].d[0].scdate, grounds[i].g[j].d[k].scdate) == 0)
        {                                                                               // if dates are equal then find the minimum time string

          if (strcmp(grounds[i].g[0].d[0].scstarttime, grounds[i].g[j].d[k].scstarttime) > 0)
          {
            strcpy(grounds[i].g[0].d[0].scstarttime, grounds[i].g[j].d[k].scstarttime);
          }
        }
      }
    }
  }
  struct ground g1[1]; 
  for (int i = 0; i < numofgrounds; i++)
  {
    for (int j = i + 1; j < numofgrounds; j++)
    {
      if (strcmp(grounds[i].g[0].d[0].scdate, grounds[j].g[0].d[0].scdate) > 0)
      {
        g1[0] = grounds[i];              // swapping of grounds if second one has less value of date 
        grounds[i] = grounds[j];
        grounds[j] = g1[0];
      }
      if (strcmp(grounds[i].g[0].d[0].scdate, grounds[j].g[0].d[0].scdate) == 0)
      {
        if (strcmp(grounds[i].g[0].d[0].scstarttime, grounds[j].g[0].d[0].scstarttime) > 0)
        {
          g1[0] = grounds[i];                         // swapping of grounds if second one has less value of time
          grounds[i] = grounds[j];
          grounds[j] = g1[0];
        }
      }
    }
  }
  for (int i = 0; i < 6; i++)
  {
    printf("\n %s ", grounds[i].groundname);
  }

  return;
}
// function to find whether the ground is available for a given game in the given dates in the given time and display the names of grounds in sorted order of their state and city names 
void isAvailable(struct ground grounds[], char gamen[], char datev[], char startt[], char endt[])
{
  struct ground temp[6];
  int count = 0;
  short flag = 0;
  for (int i = 0; i < numofgrounds; i++)
  {

    for (int j = 0; j < numofgames; j++)
    {
      if (strcmp(grounds[i].g[j].gamename, gamen) == 0)
      {
        for (int k = 0; k < numofdates; k++)
        {
          if (strcmp(grounds[i].g[j].ad[k].avstarttime, startt) <= 0)
          {
            if (strcmp(grounds[i].g[j].ad[k].avendtime, endt) >= 0)
            {

              temp[count] = grounds[i];
              count++;
              flag = 1;
            }
          }
        }
      }
    }

  } // sorting ground names on basis on state names and city names
  if (flag > 0)
  {
    for (int i = 0; i < count; i++)
    {
      for (int j = i + 1; j < count; j++)
      {
        struct ground g[1];
        if (strcmp(temp[i].state, temp[j].state) > 0)
        {
          g[0] = temp[i];
          temp[i] = temp[j];
          temp[j] = g[0];
        }
        else if (strcmp(temp[i].city, temp[j].city) > 0)
        {
          g[0] = temp[i];
          temp[i] = temp[j];
          temp[j] = g[0];
        }
      }
    }
  }
  if (flag > 0)
  {
    printf("list of grounds available for the %s game are sorted according to state name ", gamen);
    for (int i = 0; i < count; i++)
    {
      printf(" \n groumdname : %s   state name : %s   ", grounds[i].groundname, grounds[i].state);
    }
  }
  else
    printf("no  grounds available for the %s game  ", gamen);
  return;
}
// function to find the unique games in the ground for a given city
void Uniquesport(struct ground grounds[], struct ground ug, char cityv[])
{
  short count = 0;
  for (int j = 0; j < numofgames; j++)
  {
    short flag = 0;

    for (int i = 0; i < numofgrounds; i++)
    {
      if (strcmp(grounds[i].groundname, ug.groundname) != 0)
      {
        if (strcmp(ug.city, cityv) == 0)
        {
          for (int k = 0; k < numofgames; k++)
          {
            if (strcmp(ug.g[j].gamename, grounds[i].g[k].gamename) == 0)
            {

              flag = 1;
            }
          }
        }
      }
    }
    if (flag == 0)
    {
      printf(" \n %s ", ug.g[j].gamename);
      count++;
    }
  }
  if (count > 0)
  {
    printf(" \n these are the unique games at ground %s", ug.groundname);
  }
  else
    printf(" \n no unique games found at ground %s", ug.groundname);

  return;
}
// function to find the location for a given game with in the given time
void FindLocationsForGameInTimeRange(struct ground grounds[], char gamev[], char datev[], char startt[], char endt[])
{
  short f = 0;
  for (int i = 0; i < numofgrounds; i++)
  {
    int flag = 0;
    for (int j = 0; (j < numofgames) && (flag == 0); j++)
    {
      if (strcmp(grounds[i].g[j].gamename, gamev) == 0)
      {
        for (int k = 0; k < numofdates && flag == 0; k++)
        {
          if (strcmp(grounds[i].g[j].ad[k].avdate, datev) == 0)
          {
            if (strcmp(grounds[i].g[j].ad[k].avstarttime, startt) <= 0)
            {
              if (strcmp(grounds[i].g[j].ad[k].avendtime, endt) >= 0)
              {
                printf(" \n ground name : %s  city name : %s date : %s  starting time : %s endingtime : %s", grounds[i].groundname, grounds[i].city, datev, startt, endt);
                flag = 1;
                f = 1;
              }
            }
          }
        }
      }
    }
  }
  if (f > 0)
  {
    printf("\n these locations for  %s game can be scheduled in  given time", gamev);
  }
  else
    printf(" \n  no locations  found for game : %s  during the given time are ", gamev);
  return;
}
// function to find the clash between grounds for a given game in the given time
void ClashofMatches(struct ground grounds[], char gamev[], char datev[])
{

  int count = 0;
  char g1[30];

  for (int i = 0; i < numofgrounds; i++)
  {
    for (int j = 0; j < numofgrounds; j++)
    {
      if (strcmp(grounds[i].g[j].gamename, gamev) == 0)
      {
        for (int k = 0; k < numofdates; k++)
        {
          if (strcmp(grounds[i].g[j].d[k].scdate, datev) == 0)
          {
            count++;
          }
        }
      }
    }
    if (count == 1)
    {
      strcpy(g1, grounds[i].groundname);
    }
    if (count >= 2)
    {
      printf("\n %s", grounds[i].groundname);
    }
  }
  if (count > 1)
  {
    printf("\n %s", g1);
    printf("these are the  clashes between grounds for the  game %s   ", gamev);
  }
  else
    printf("there are no clashes between grounds for the game %s", gamev);
  return;
}
// function to display list of grounds having at least k matches in the given city
void GiveListofGroundshavingatlestKmatches(struct ground grounds[], char datev[], char cityv[], int k)
{
  int count;
  int flag = 0;
  for (int i = 0; i < numofgrounds; i++)
  {
    count = 0;
    if (strcmp(grounds[i].city, cityv) == 0)
    {
      for (int j = 0; j < numofgames; j++)
      {
        for (int k = 0; k < numofdates; k++)
        {
          if (strcmp(grounds[i].g[j].d[k].scdate, datev) == 0)
          {
            count++;
          }
        }
      }
    }

    if (count >= k)
    {
      printf("\n %s", grounds[i].groundname);
      flag = 1;
    }
  }
  if (flag == 0)
  {
    printf("no grounds having atleast %d matches in city %s", k, cityv);
  }
  else
    printf("these are the grounds having atleast %d matches in city %s", k, cityv);
  return;
}
// function to sort the grounds by prize for the given game 
void SortOnPriceForaGame(struct ground grounds[], char gamev[], char datev[], char startt[], char endt[])
{
  int count = 0;
  struct ground temp[6];
  int flag = 0;
  for (int i = 0; i < numofgrounds; i++)
  {
    for (int j = 0; j < numofgames; j++)
    {
      if (strcmp(gamev, grounds[i].g[j].gamename) == 0)
      {
        for (int k = 0; k < numofdates; k++)
        {

          if (strcmp(datev, grounds[i].g[j].ad[k].avdate) == 0)
          {

            if ((strcmp(startt, grounds[i].g[j].ad[k].avstarttime)) >= 0)
            {
              if ((strcmp(endt, grounds[i].g[j].ad[k].avendtime)) <= 0)
              {
                temp[count] = grounds[i];
                count++;
                flag = 1;
              }
            }
          }
        }
      }
    }
  }
  struct ground t[1];
  if (count > 0)
  {
    for (int i = 0; i < numofgrounds; i++)
    {
      for (int j = 0; j < numofgames; j++)
      {
        if (strcmp(gamev, temp[i].g[j].gamename) == 0)
        {
          for (int k = i + 1; k < numofgrounds; k++)
          {
            for (int l = 0; l < numofgames; l++)
            {
              if (strcmp(gamev, temp[k].g[l].gamename) == 0)
              {

                if (grounds[i].g[j].hourlygamerate < grounds[k].g[l].hourlygamerate)
                {
                  t[0] = temp[1];
                  temp[i] = temp[k];
                  temp[k] = t[0];
                }
              }
            }
          }
        }
      }
    }

    for (int i = 0; i < numofgrounds; i++)
    {
      printf("\n %s   ", temp[i].groundname);
    }
    printf("these are the grounds available for the game sorted on prize wise ");
  }
  else
    printf("no grounds found for this game");

  return;
}

int main()
{

  struct ground a[6];
  // giving data for the ground structures
  // first ground
  strcpy(a[0].groundname, "narendra modi stadium");
  strcpy(a[0].city, " ahemadabad");
  strcpy(a[0].state, "gujarat");
  strcpy(a[0].g[0].gamename, "cricket");
  a[0].g[0].hourlygamerate = 290;
  strcpy(a[0].g[0].d[0].scdate, "2004/09/03");
  strcpy(a[0].g[0].d[0].scstarttime, "06:30");
  strcpy(a[0].g[0].d[0].scendtime, "08:30");
  strcpy(a[0].g[0].d[1].scdate, "2004/09/05");
  strcpy(a[0].g[0].d[1].scstarttime, "07:30");
  strcpy(a[0].g[0].d[1].scendtime, "09:30");
  strcpy(a[0].g[0].d[2].scdate, "2004/10/03");
  strcpy(a[0].g[0].d[2].scstarttime, "06:30");
  strcpy(a[0].g[0].d[2].scendtime, "07:30");
  strcpy(a[0].g[0].ad[0].avdate, "2006/10/25");
  strcpy(a[0].g[0].ad[0].avstarttime, "05:00");
  strcpy(a[0].g[0].ad[0].avendtime, "22:30");
  strcpy(a[0].g[0].ad[1].avdate, "2004/10/05");
  strcpy(a[0].g[0].ad[1].avstarttime, "07:30");
  strcpy(a[0].g[0].ad[1].avendtime, "20:30");
  strcpy(a[0].g[0].ad[2].avdate, "2004/07/09");
  strcpy(a[0].g[0].ad[2].avstarttime, "06:30");
  strcpy(a[0].g[0].ad[2].avendtime, "18:30");
  // second ground
  strcpy(a[1].groundname, "vivekananda stadium");
  strcpy(a[1].city, " kolkata");
  strcpy(a[1].state, "west bengal");
  strcpy(a[1].g[0].gamename, "athletics");
  a[1].g[0].hourlygamerate = 300;
  strcpy(a[1].g[0].d[0].scdate, "2004/03/03");
  strcpy(a[1].g[0].d[0].scstarttime, "06:30");
  strcpy(a[1].g[0].d[0].scendtime, "08:30");
  strcpy(a[1].g[0].d[1].scdate, "2004/05/04");
  strcpy(a[1].g[0].d[1].scstarttime, "07:30");
  strcpy(a[1].g[0].d[1].scendtime, "08:30");
  strcpy(a[1].g[0].ad[0].avdate, "2004/09/03");
  strcpy(a[1].g[0].ad[0].avstarttime, "05:30");
  strcpy(a[1].g[0].ad[0].avendtime, "20:30");
  strcpy(a[1].g[0].ad[1].avdate, "2004/05/04");
  strcpy(a[1].g[0].ad[1].avstarttime, "07:30");
  strcpy(a[1].g[0].ad[1].avendtime, "20:30");
  strcpy(a[1].g[1].gamename, "football");
  a[1].g[1].hourlygamerate = 500;
  strcpy(a[1].g[1].d[0].scdate, "2004/03/25");
  strcpy(a[1].g[1].d[0].scstarttime, "06:30");
  strcpy(a[0].g[0].d[0].scendtime, "07:45");
  strcpy(a[1].g[1].d[1].scdate, "2004/03/24");
  strcpy(a[1].g[1].d[1].scstarttime, "07:30");
  strcpy(a[1].g[1].d[1].scendtime, "08:30");
  strcpy(a[1].g[1].ad[0].avdate, "2004/05/23");
  strcpy(a[1].g[1].ad[0].avstarttime, "06:30");
  strcpy(a[0].g[0].ad[0].avendtime, "20:45");
  strcpy(a[1].g[1].ad[1].avdate, "2004/06/25");
  strcpy(a[1].g[1].ad[1].avstarttime, "07:30");
  strcpy(a[1].g[1].ad[1].avendtime, "22:30");
  strcpy(a[1].g[2].gamename, "cricket");
  a[1].g[2].hourlygamerate = 900;

  strcpy(a[1].g[2].d[0].scdate, "2004/09/03");
  strcpy(a[1].g[2].d[0].scstarttime, "06:30");
  strcpy(a[1].g[2].d[0].scendtime, "09:30");
  strcpy(a[1].g[2].d[1].scdate, "2004/04/05");
  strcpy(a[1].g[2].d[1].scstarttime, "18:30");
  strcpy(a[1].g[2].d[1].scendtime, "20:30");
  strcpy(a[1].g[2].ad[0].avdate, "2004/04/05");
  strcpy(a[1].g[2].ad[0].avstarttime, "06:30");
  strcpy(a[1].g[2].ad[0].avendtime, "20:30");
  strcpy(a[1].g[2].ad[1].avdate, "2006/10/25");
  strcpy(a[1].g[2].ad[1].avstarttime, "05:30");
  strcpy(a[1].g[2].ad[1].avendtime, "20:30");
  // third ground
  strcpy(a[2].groundname, "jawaharlal nehru sports complex");
  strcpy(a[2].city, "delhi");
  strcpy(a[2].state, "odisha");
  strcpy(a[2].g[0].gamename, "gymnastics");
  a[2].g[0].hourlygamerate = 400;
  strcpy(a[2].g[0].d[0].scdate, "2006/10/25");
  strcpy(a[2].g[0].d[0].scstarttime, "10:30");
  strcpy(a[2].g[0].d[0].scendtime, "12:30");
  strcpy(a[2].g[0].ad[0].avdate, "2004/03/05");
  strcpy(a[2].g[0].ad[0].avstarttime, "10:30");
  strcpy(a[2].g[0].ad[0].avendtime, "20:30");

  strcpy(a[2].g[0].ad[1].avdate, "2004/08/02");
  strcpy(a[2].g[0].ad[1].avstarttime, "06:30");
  strcpy(a[2].g[0].ad[1].avendtime, "22:30");
  strcpy(a[2].g[0].ad[2].avdate, "2004/03/09");
  strcpy(a[2].g[0].ad[2].avstarttime, "07:30");
  strcpy(a[2].g[0].ad[2].avendtime, "20:30");
  strcpy(a[2].g[1].gamename, "cricket");
  a[2].g[1].hourlygamerate = 500;
  strcpy(a[2].g[1].d[0].scdate, "2005/03/03");
  strcpy(a[2].g[1].d[0].scstarttime, "20:30");
  strcpy(a[2].g[1].d[0].scendtime, "22:30");
  strcpy(a[2].g[1].d[1].scdate, "2004/03/09");
  strcpy(a[2].g[1].d[1].scstarttime, "20:30");
  strcpy(a[2].g[1].d[1].scendtime, "22:30");
  strcpy(a[2].g[1].ad[0].avdate, "2004/06/07");
  strcpy(a[2].g[1].ad[0].avstarttime, "09:30");
  strcpy(a[2].g[1].ad[0].avendtime, "22:30");
  strcpy(a[2].g[1].ad[1].avdate, "2004/03/06");
  strcpy(a[2].g[1].ad[1].avstarttime, "07:30");
  strcpy(a[2].g[1].ad[1].avendtime, "22:30");

  strcpy(a[2].g[2].gamename, "badminton");
  a[2].g[2].hourlygamerate = 700;
  strcpy(a[2].g[2].d[0].scdate, "2005/11/09");
  strcpy(a[2].g[2].d[0].scstarttime, " 05:30");
  strcpy(a[2].g[2].d[0].scendtime, "08:30");
  strcpy(a[2].g[2].d[1].scdate, "2005/04/03");
  strcpy(a[2].g[2].d[1].scstarttime, " 05:30");
  strcpy(a[2].g[2].d[1].scendtime, "08:00");
  strcpy(a[2].g[2].ad[0].avdate, "2005/03/04");
  strcpy(a[2].g[2].ad[0].avstarttime, " 05:30");
  strcpy(a[2].g[2].ad[0].avendtime, "22:30");
  strcpy(a[2].g[2].ad[1].avdate, "2005/03/02");
  strcpy(a[2].g[2].ad[1].avstarttime, " 05:30");
  strcpy(a[2].g[2].ad[1].avendtime, "20:00");
  // fourth ground
  strcpy(a[3].groundname, "netaji indoor sports complex");
  strcpy(a[3].city, "kolkata");
  strcpy(a[3].state, "west bengal");
  strcpy(a[3].g[0].gamename, "cricket");
  a[3].g[0].hourlygamerate = 600;
  strcpy(a[3].g[0].d[0].scdate, "2004/03/03");
  strcpy(a[3].g[0].d[0].scstarttime, "06:30");
  strcpy(a[3].g[0].d[0].scendtime, "08:30");
  strcpy(a[3].g[0].d[1].scdate, "2005/06/20");
  strcpy(a[3].g[0].d[1].scstarttime, "18:30");
  strcpy(a[3].g[0].d[1].scendtime, "20:30");
  strcpy(a[3].g[0].ad[0].avdate, "2005/02/09");
  strcpy(a[3].g[0].ad[0].avstarttime, "06:30");
  strcpy(a[3].g[0].ad[0].avendtime, "20:30");
  strcpy(a[3].g[0].ad[1].avdate, "2006/10/25");
  strcpy(a[3].g[0].ad[1].avstarttime, "08:30");
  strcpy(a[3].g[0].ad[1].avendtime, "20:30");
  strcpy(a[3].g[1].gamename, "tennis");

  a[3].g[1].hourlygamerate = 300;
  strcpy(a[3].g[1].d[0].scdate, "2005/06/20");
  strcpy(a[3].g[1].d[0].scstarttime, "06:30");
  strcpy(a[3].g[1].d[0].scendtime, "09:30");
  strcpy(a[3].g[1].d[1].scdate, "2005/06/08");
  strcpy(a[3].g[1].d[1].scstarttime, "20:30");
  strcpy(a[3].g[1].d[1].scendtime, "22:30");
  strcpy(a[3].g[1].ad[0].avdate, "2005/05/03");
  strcpy(a[3].g[1].ad[0].avstarttime, "06:30");
  strcpy(a[3].g[1].ad[0].avendtime, "20:30");
  strcpy(a[3].g[1].ad[1].avdate, "2005/08/02");
  strcpy(a[3].g[1].ad[1].avstarttime, "07:30");
  strcpy(a[3].g[1].ad[1].avendtime, "22:30");
  // fifthground
  strcpy(a[4].groundname, "gandhi ground");
  strcpy(a[4].city, "delhi");
  strcpy(a[4].state, "rajasthan");
  strcpy(a[4].g[0].gamename, "hockey");
  a[4].g[0].hourlygamerate = 500;
  strcpy(a[4].g[0].d[0].scdate, "2005/03/09");
  strcpy(a[4].g[0].d[0].scstarttime, "17:30");
  strcpy(a[4].g[0].d[0].scendtime, "20:30");
  strcpy(a[4].g[0].d[1].scdate, "2005/04/09");
  strcpy(a[4].g[0].d[1].scstarttime, "20:30");
  strcpy(a[4].g[0].d[1].scendtime, "22:30");
  strcpy(a[4].g[0].d[2].scdate, "2005/04/27");
  strcpy(a[4].g[0].d[2].scstarttime, "19:00");
  strcpy(a[4].g[0].d[2].scendtime, "21:30");
  strcpy(a[4].g[0].ad[0].avdate, "2005/09/03");
  strcpy(a[4].g[0].ad[0].avstarttime, "07:30");
  strcpy(a[4].g[0].ad[0].avendtime, "20:30");
  strcpy(a[4].g[0].ad[1].avdate, "2005/04/10");
  strcpy(a[4].g[0].ad[1].avstarttime, "08:30");
  strcpy(a[4].g[0].ad[1].avendtime, "22:30");
  strcpy(a[4].g[0].ad[2].avdate, "2005/04/26");
  strcpy(a[4].g[0].ad[2].avstarttime, "09:00");
  strcpy(a[4].g[0].ad[2].avendtime, "21:30");
  strcpy(a[4].g[1].gamename, "cricket");
  a[4].g[1].hourlygamerate = 900;
  strcpy(a[4].g[1].d[0].scdate, "2006/10/25");
  strcpy(a[4].g[1].d[0].scstarttime, "15:30");
  strcpy(a[4].g[1].d[0].scendtime, "18:30");
  strcpy(a[4].g[1].d[1].scdate, "2005/02/09");
  strcpy(a[4].g[1].d[1].scstarttime, "20:30");
  strcpy(a[4].g[1].d[1].scendtime, "22:30");

  strcpy(a[4].g[1].ad[0].avdate, "2006/10/25");
  strcpy(a[4].g[1].ad[0].avstarttime, "05:30");
  strcpy(a[4].g[1].ad[0].avendtime, "18:30");
  strcpy(a[4].g[1].ad[1].avdate, "2005/03/07");
  strcpy(a[4].g[1].ad[1].avstarttime, "06:30");
  strcpy(a[4].g[1].ad[1].avendtime, "22:30");
  strcpy(a[4].g[2].gamename, "foot ball");
  a[4].g[2].hourlygamerate = 300;
  strcpy(a[4].g[2].d[0].scdate, "2004/04/03");
  strcpy(a[4].g[2].d[0].scstarttime, "06:30");
  strcpy(a[4].g[2].d[0].scendtime, "08:30");
  strcpy(a[4].g[2].d[1].scdate, "2005/07/09");
  strcpy(a[4].g[2].d[1].scstarttime, "06:30");
  strcpy(a[4].g[2].d[1].scendtime, "09:30");
  strcpy(a[4].g[2].ad[0].avdate, "2005/04/02");
  strcpy(a[4].g[2].ad[0].avstarttime, "06:30");
  strcpy(a[4].g[2].ad[0].avendtime, "20:30");
  strcpy(a[4].g[2].ad[1].avdate, "2005/09/07");
  strcpy(a[4].g[2].ad[1].avstarttime, "06:30");
  strcpy(a[4].g[2].ad[1].avendtime, "19:30");
  // sixthground
  strcpy(a[5].groundname, "rk khana tennis ground");
  strcpy(a[5].city, "delhi");
  strcpy(a[5].state, "delhi");
  strcpy(a[5].g[0].gamename, "tennis");
  a[5].g[0].hourlygamerate = 900;
  strcpy(a[5].g[0].d[0].scdate, "2005/04/02");
  strcpy(a[5].g[0].d[0].scstarttime, "05:30");
  strcpy(a[5].g[0].d[0].scendtime, "07:30");
  strcpy(a[5].g[0].d[1].scdate, "2005/09/07");
  strcpy(a[5].g[0].d[1].scstarttime, "09:30");
  strcpy(a[5].g[0].d[1].scendtime, "11:30");
  strcpy(a[5].g[0].d[2].scdate, "2006/10/25");

  strcpy(a[5].g[0].d[2].scstarttime, "08:30");
  strcpy(a[5].g[0].d[2].scendtime, "10:30");
  strcpy(a[5].g[0].ad[0].avdate, "2005/08/02");
  strcpy(a[5].g[0].ad[0].avstarttime, "05:30");
  strcpy(a[0].g[0].ad[0].avendtime, "20:30");
  strcpy(a[5].g[0].ad[1].avdate, "2005/04/02");
  strcpy(a[5].g[0].ad[1].avstarttime, "09:30");
  strcpy(a[5].g[0].ad[1].avendtime, "20:30");
  strcpy(a[5].g[0].ad[2].avdate, "2005/05/09");
  strcpy(a[5].g[0].ad[2].avstarttime, "08:30");
  strcpy(a[5].g[0].ad[2].avendtime, "20:30");
  struct ground g1[1];
  // sorting based on the name of grounds 
  for (int i = 0; i < 6; i++)
  {
    for (int j = i + 1; j < 6; j++)
    {
      if (strcmp(a[i].groundname, a[j].groundname) > 0)
      {
        g1[0] = a[i];
        a[i] = a[j];
        a[j] = g1[0];
      }
    }
  }
  printf("available options for you are:\n");
  printf("1.Lists the games scheduled in the city sorted according to the ground name and sport name\n");
  printf("2.list of grounds sorted according to the date and time\n");
  printf("3.list of grounds available on the date and time sorted according to the state and city names\n");
  printf("4.List of sports taking place on a ground which are unique (do not happen on other grounds) in the city\n");
  printf("5.List of grounds (with their cities) where a particular game can be scheduled to be played at a particular time\n");
  printf("6.List all the clashing matches for a given game on a given date among the list-of-grounds input\n");
  printf("7.List of grounds in the city having atleast K matches in total on a given day for any of the games in the list\n");
  printf("8.List of grounds sorted based on the prices for the given game on given date and time.\n");
  int n;
  printf("enter the number corresponding to your desired option");
  scanf("%d", &n);

  switch (n)
  {
  case 1:

              char cityv[30];
                char datev[10];
              char starttime[10];
              char endtime[10];
               printf("enter the city name:");
              scanf("%s", cityv);
                printf("enter date :");
             scanf("%s", datev);
              printf("enter start time :");
             scanf("%s", starttime);
            printf("enter end time :");
            scanf("%s", endtime);

           getFixturesinCity(a, cityv, datev, starttime, endtime);
            break;

  case 2:

            getFixturesSortedonDate(a);
              break;

  case 3:

            char gamev[20];
             char datev[10];
             char starttime[10], endtime[10];
            printf("enter name of game:");
             scanf("%s", gamev);
              printf("enter date :");
               scanf("%s", datev);
               printf("enter starttime:");
              scanf("%s", starttime);
              printf("enter end time :");
             scanf("%s", endtime);

               isAvailable(a, gamev, datev, starttime, endtime);
              break;

  case 4:

               int i;
               char cityv[20];
                   printf("enter ground number to find the UniqueSports in that ground :");
                       scanf("%d", i);
                 printf("enter city name:");
                      scanf("%s", cityv);

               UniqueSports(a, a[i], cityv);
               break;

  case 5:

                        char game_n[30];
               char date[10], starttime[10], endtime[10];
                     printf("enter the game name:");
               scanf("%s", game_n);
               printf("enter date :");
                 scanf("%s", date);
              printf("enter start time :");
               scanf("%s", starttime);
              printf("enter end time :");
                scanf("%s", endtime);

              FindLocationsForGameInTimeRange(a, game_n, date, starttime, endtime);
                 break;

  case 6:

              char gamev[30];
              char datev[10];
               printf("enter the game name:");
              scanf("%s", gamev);
             printf("enter date :");
              scanf("%s", datev);
               ClashofMatches(a, gamev, datev);
                break;

  case 7:
               char cityv[30];
              char datev[10];
               int k;
                  printf("enter the city name:");
                scanf("%s", cityv);
                 printf("enter date :");
                scanf("%s", datev);
                     printf("enter number of matches that you want to check in the city ");
               scanf("%d", &k);

                GiveListofGroundshavingatlestKmatches(a, datev, cityv, k);
                      break;

  case 8:
               char gamev[30];
                  char datev[10];
                  char starttime[10];
                  char endtime[10];
               printf("enter the game name:");
                 scanf("%s", gamev);
                   printf("enter date :");
               scanf("%s", datev);
               printf("enter starting time :");
                   scanf("%s", starttime);
                printf("enter ending time :");
                  scanf("%s", endtime);

                    SortOnPriceForaGame(a, gamev, datev, starttime, endtime);

                      break;
  default:
       printf(" sorry we dont have that option with us");
  }

  return 0;
}
