/*
 * epollnet.h
 *
 *  Created on: 2015年10月23日
 *      Author: hult
 */

#ifndef EPOLLNET_H_
#define EPOLLNET_H_
#ifdef _EPOLL_ET_MODE
//綁定epoll監聽端口
int epoll_bind(int port);
//將acfd添加到epoll中
int epoll_add_acfd(int acfd);
//非阻塞
int epoll_set_nonblock(int fd) ;
//注冊到epoll
int epoll_new_conn(int sfd) ;
//從epoll中移除
int epoll_close_conn(int sfd);
//讀epoll
int epoll_mod_read(int sfd) ;
//寫epoll
int epoll_mod_write(int sfd) ;

//啓動封包處理綫程
int Start_PacketWrapper();
//啓動epoll主循環綫程
int Start_Epoll_Loop();
//int Start_Epoll_SendLoop();
#endif
#endif /* EPOLLNET_H_ */
