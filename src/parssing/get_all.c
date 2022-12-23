/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:21:26 by yaskour           #+#    #+#             */
/*   Updated: 2022/12/23 16:22:48 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/include.h"

int get_metadata(t_all *data)
{
  if (get_ceiling(data))
    return (0);
  if (get_floor(data))
    return (0);
  if (get_north(data))
    return (0);
  if (get_south(data))
    return (0);
  if (get_east(data))
    return (0);
  if (get_west(data))
    return (0);
  return (1);
}

void get_map(t_all *data)
{
  int i;
  int j;

  i = data->parss.map_index;
  while(data->parss.all[i])
    i++;
  data->parss.map = malloc(sizeof(char *) * i + 1);
  i = data->parss.map_index;
  j = 0;
  while(data->parss.all[i])
  {
    data->parss.map[j] = ft_strdup(data->parss.all[i]);
    i++;
    j++;
  }
  free_all(data);
}
