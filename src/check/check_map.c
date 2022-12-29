/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:24:25 by yaskour           #+#    #+#             */
/*   Updated: 2022/12/29 17:54:14 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

unsigned int big_len(t_all *data)
{
  unsigned int len;
  int i;


  i = 0;
  len = 0;
  while (data->valid.maps[i])
  {
    if (len < ft_strlen(data->valid.maps[i]))
      len = ft_strlen(data->valid.maps[i]);
    i++;
  }
  return (len);
}

void str_space(char **dest,char *original,unsigned int b_len)
{
  char *to_fill;
  int len;
  int diff;
  len = ft_strlen(original);
  diff = b_len - len;
  to_fill = malloc(sizeof(char)  * (len  + diff + 1));
  int i;

  i = 0;

  while(original[i])
  {
    to_fill[i] = original[i];
    i++;
  }
  while(diff)
  {
    to_fill[i] = ' '; 
    i++;
    diff--;
  }
  to_fill[i] = '\0';
  *dest = to_fill;
}

void add_space(t_all *data)
{
  char **map;
  int i;
  int b_len;

  
  b_len = big_len(data);
  data->valid.line_len = b_len;
  i = 0;
  while(data->valid.maps[i])
    i++;
  map = malloc(sizeof(char *) * (i + 1));
  if (!map)
    return ;
  i = 0;
  while (data->valid.maps[i])
  {
    str_space(&map[i],data->valid.maps[i],b_len);
    free(data->valid.maps[i]);
    i++;
  }
  map[i] = NULL;
  free(data->valid.maps);
  data->valid.maps = map;
}


int endmap_index(char **str)
{
  int i;

  i = 0;
  while (str[i])
    i++;
  i--;
  while (str[i])
  {
    if (ft_strlen(str[i]) && is_empty(str[i]))
      break;
    i--;
  }
  return (i);
}

void init_map(t_all *data)
{
  int i;

  int end;
  end = endmap_index(data->parss.map);
  data->valid.maps = malloc(sizeof(char *) * (end + 2));

  i = 0;
  while (i <= end)
  {
    data->valid.maps[i] = ft_strdup(data->parss.map[i]);
    i++;
  }
  data->valid.map_len = i;
  data->valid.maps[i] = NULL;
  free_map(data);
}

int search(char *src,char *str)
{
  int i;
  i = 0;

  while (src[i])
  {
    if (!ft_strchr(str,src[i]))
      return (1);
    i++;
  }
  return (0);
};

int check_characters(t_all *data)
{
  int i;

  i = 0;
  while (data->valid.maps[i])
  {
    if (search(data->valid.maps[i],"10 NSEW"))
      return (1);
    i++;
  }
  return (0);
}

int first_and_last_char(char **str,int map_len,int line_len)
{
  int i;
  int j;

  i = 1;
  while (i < map_len - 1)
  {
    j = 0;
    while (str[i][j] && str[i][j] == ' ')
      j++;
    if (str[i][j] != '1')
      return (1);
    j = line_len - 1;
    while (j > 0 && str[i][j] == ' ')
      j--;
    if (str[i][j] != '1')
      return (1);
    i++;
  }
  return (0);
}

int middle_char(t_all *data)
{
  int i;
  int j;
  int start;
  int end;

  i = 1;
  while (i < data->valid.map_len - 1)
  {
    start = 0;
    while (data->valid.maps[i][start] && data->valid.maps[i][start] == ' ')
      start++;
    end = data->valid.line_len - 1;
    while (end > 0 && data->valid.maps[i][end] == ' ')
      end--;
    j = start;
    while (j < end)
    {
      //printf("%c",data->valid.maps[i][j]);
      if (data->valid.maps[i][j] == ' ')
      {
        if (data->valid.maps[i][j - 1] != '1' && data->valid.maps[i][j - 1] != ' ') 
          return (1);
        if (data->valid.maps[i][j + 1] != '1' && data->valid.maps[i][j + 1] != ' ') 
          return (1);
        if (data->valid.maps[i - 1][j] != '1' && data->valid.maps[i - 1][j] != ' ') 
          return (1);
        if (data->valid.maps[i + 1][j] != '1' && data->valid.maps[i + 1][j] != ' ') 
          return (1);
      }
      if (data->valid.maps[i][j] == '0')
      {
        if (data->valid.maps[i][j - 1] == ' ') 
        {
          printf("a\n");
          return (1);
        }
        if (data->valid.maps[i][j + 1] == ' ') 
        {
          printf("b\n");
          return (1);
        }
        if (data->valid.maps[i - 1][j] == ' ') 
        {
          printf("c\n");
          return (1);
        }
        if (data->valid.maps[i + 1][j] == ' ') 
        {
          printf("i = %d j = %d -> %c\n",i,j,data->valid.maps[i + 1][j]);
          return (1);
        }
      }
      j++;
    }
    //printf("\n");
    i++;
  }
  return (0);
}

int check_valid_map(t_all *data)
{
  if (search(data->valid.maps[0]," 1"))
    return (1);
 if (search(data->valid.maps[data->valid.map_len -1]," 1"))
   return (1);
 if (first_and_last_char(data->valid.maps,data->valid.map_len,data->valid.line_len))
   return (1);
 if (middle_char(data))
   return (1);
  return (0);
}

int check_map(t_all *data)
{
  init_map(data);
  add_space(data);
  if (check_characters(data))
  {
    free_maps(data);
    printf("invalid map characters\n");
    return (1);
  }
  if (check_valid_map(data))
  {
    printf("invalid map \n");
    return (1);
  }
  free_maps(data);
  return (0);
}
