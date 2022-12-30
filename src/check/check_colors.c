/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:51:35 by yaskour           #+#    #+#             */
/*   Updated: 2022/12/30 22:00:41 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/include.h"

int check_floor(t_all *data)
{
  char **rgb;
  int   j;
  char *trimed_str;

  if (data->parss.floor[1] != ' ')
    return (0);
  trimed_str = ft_strtrim(&data->parss.floor[1]," ");
  j = cout_comma(trimed_str);
  if (j == 2)
  {
    rgb = ft_split(trimed_str,',');
    free(trimed_str);
    if (check_is_rgb(rgb))
    {
      free_rgb(rgb);
      return (0);
    }
    if (fill_floor(rgb,data))
    {
      free_rgb(rgb);
      return (0);
    }
    free_rgb(rgb);
    return (1);
  }
  return (0);
}

int check_ceiling(t_all *data)
{
  char **rgb;
  int   j;
  char *trimed_str;

  if (data->parss.ceiling[1] != ' ')
    return (0);
  trimed_str = ft_strtrim(&data->parss.ceiling[1]," ");
  j = cout_comma(trimed_str);
  if (j == 2)
  {
    rgb = ft_split(trimed_str,',');
    free(trimed_str);
    if (check_is_rgb(rgb))
    {
      free_rgb(rgb);
      return (0);
    }
    if (fill_ceiling(rgb,data))
    {
      free_rgb(rgb);
      return (0);
    }
    free_rgb(rgb);
    return (1);
  }
  return (0);
}

int check_colors(t_all *data)
{
  if (!check_ceiling(data))
  {
    free_map(data);
    free_parssing(data);
    printf("check ceiling\n");
    return (1);
  }
  if (!check_floor(data))
  {
    free_map(data);
    free_parssing(data);
    printf("check floor\n");
    return (1);
  }
  free(data->parss.floor);
  free(data->parss.ceiling);
  return (0);
}
