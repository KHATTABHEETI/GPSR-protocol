#ifndef _GPSRCDTABLE_HPP
#define _GPSRCDTABLE_HPP


#include "config.h"
#include "packet.h"
#include "gpsr_packet.h"

struct cooentry 
{
  node_info node_;
  nsaddr_t lasthop_;                                 //���һ��
  int hops_;                                              //���� ���ڱȽ�����·��
  int seqno_;                                            // ��ӦrequestAskCounter_ ����
  float ts_;                                                // ʱ��
  struct cooentry *next ;
  bool isNodeHere () const 
  {
    return ( seqno_ == -1  ) ? false : true ; 
  }
  bool operator == ( const struct cooentry &other ) const {
    if ( node_.id_ == other.node_.id_ 
	 && node_.x_ == other.node_.x_
	 && node_.y_ == other.node_.y_
	 && lasthop_ == other.lasthop_
	 && hops_  == other.hops_
	 && seqno_ == other.seqno_
	 ) {

      return true; 
    }
    return false ; 
  }
};



class cdtable {
private:
  cooentry *coordinatelist_;
  int coornum_;
public:
  cdtable();
  ~cdtable();
  bool add (  const struct cooentry &  entry );                                  //����������Ϣ
  bool add ( const struct packet_info & info, nsaddr_t lasthop, int hops ) ; 
                  
  bool remove ( nsaddr_t id );
  bool getEntrybyID ( nsaddr_t id , struct cooentry * &entry );
  bool isEntry ( nsaddr_t id );

  void delAllTimeout ( double useful_period ) ; 
  static cooentry makeNNEntry ( nsaddr_t id ); 
  unsigned size () const { return coornum_ ;  }
private:
  bool _findentry ( nsaddr_t id, cooentry *&pre, cooentry *&current  );
  bool _delAll ();
};



struct helpoutentry {
  nsaddr_t wheretogo_;                              
  nsaddr_t  shouldgo_;                               //  ������cdtable��
  unsigned int seqno_; 
  float ts_;
  int hops_;                                                // ����С ����
  struct helpoutentry *next; 
};


class helpoutdata  {
private:
  struct helpoutentry * hlist_;
  unsigned int num_; 

public :
  helpoutdata () 
  {
    hlist_ = NULL;
    num_ = 0; 
  }
  ~helpoutdata ()
  {
    _delAll ();
  }
  bool add ( const struct helpoutentry & entry );
  bool  remove ( nsaddr_t  id );
  bool getEntrybyID ( nsaddr_t id , struct helpoutentry *& entry );
  void delAllTimeout ( double useful_period ) ; 
private:
  bool  _findentry ( nsaddr_t id, struct helpoutentry *& pre, struct helpoutentry *& cur  );
  void _delAll () ; 
}; 


#endif 


