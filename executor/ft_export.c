#include "minishell.h"
//
//t_list *insert_srt (t_list **sort_list, t_var *var)
//{
//	t_list	*tmp_list;
//	t_var	*tmp_var;
//
//	tmp_var = (t_var *)sort_list->content;
//	tmp_list = sort_list;
//	if (!sort_list->content || strcmp(var->name, tmp_var->name) < 0)
//	{
//		sort_list->Next = tmp_list;
//		list = item;
//	}
//	else {
//		for (struct spis *p = list; p; p = p->Next)
//			if (p->Next == 0 || strcmp(item->name, p->Next->name) < 0) {
//				item->Next = p->Next;
//				p->Next = item;
//				break;
//			}
//	}
//
//	return list;
//}
//
//struct spis *
//sort_list (struct spis *list)
//{
//	struct spis *sl = 0;
//
//	while (list) {
//		struct spis *p = list;
//		list = list->Next;
//		sl = insert_srt(sl, p);
//	}
//
//	return sl;
//}

int		ft_export( char **args,  t_list **var_list)
{
	(void)args;
	(void)var_list;
	printf("ft_export\n");
	return(0);
}

