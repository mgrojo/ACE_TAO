// $Id$

#include "tao/Synch_Reply_Dispatcher.h"
#include "tao/ORB_Core.h"
#include "tao/Wait_Strategy.h"
#include "tao/Pluggable_Messaging_Utils.h"
#include "Transport.h"

ACE_RCSID(tao, Synch_Reply_Dispatcher, "$Id$")


// Constructor.
TAO_Synch_Reply_Dispatcher::TAO_Synch_Reply_Dispatcher (
    TAO_ORB_Core *orb_core,
    IOP::ServiceContextList &sc
  )
  : reply_service_info_ (sc),
    reply_received_ (0),
    orb_core_ (orb_core),
    wait_strategy_ (0),
    buf_ (),
    db_ (sizeof buf_,
         ACE_Message_Block::MB_DATA,
         this->buf_,
         this->orb_core_->message_block_buffer_allocator (),
         this->orb_core_->locking_strategy (),
         ACE_Message_Block::DONT_DELETE,
         this->orb_core_->message_block_dblock_allocator ()),
    reply_cdr_ (&db_,
                ACE_Message_Block::DONT_DELETE,
                TAO_ENCAP_BYTE_ORDER,
                TAO_DEF_GIOP_MAJOR,
                TAO_DEF_GIOP_MINOR,
                orb_core),
    leader_follower_condition_variable_ (0)
{
}

// Destructor.
TAO_Synch_Reply_Dispatcher::~TAO_Synch_Reply_Dispatcher (void)
{
}

TAO_InputCDR &
TAO_Synch_Reply_Dispatcher::reply_cdr (void)
{
  return this->reply_cdr_;
}

int&
TAO_Synch_Reply_Dispatcher::reply_received (void)
{
  return this->reply_received_;
}

int
TAO_Synch_Reply_Dispatcher::dispatch_reply (
    TAO_Pluggable_Reply_Params &params)
{
  this->reply_status_ = params.reply_status_;

  // Steal the buffer, that way we don't do any unnecesary copies of
  // this data.
  CORBA::ULong max = params.svc_ctx_.maximum ();
  CORBA::ULong len = params.svc_ctx_.length ();
  IOP::ServiceContext* context_list = params.svc_ctx_.get_buffer (1);
  this->reply_service_info_.replace (max, len, context_list, 1);

  // Must reset the message state, it is possible that the same reply
  // dispatcher is used because the request must be re-sent.
  //this->message_state_.reset (0);

  // Transfer the <params.input_cdr_>'s content to this->reply_cdr_
  ACE_Data_Block *db =
    this->reply_cdr_.clone_from (params.input_cdr_);

  ACE_UNUSED_ARG (db);

  if (this->wait_strategy_ != 0)
    {
      if (this->wait_strategy_->reply_dispatched (
                    this->reply_received_,
                    this->leader_follower_condition_variable_
                  )
          == -1)
        {
          return -1;
        }
    }

  return 1;
}

void
TAO_Synch_Reply_Dispatcher::dispatcher_bound (TAO_Transport *transport)
{
  this->wait_strategy_ = transport->wait_strategy ();
  this->leader_follower_condition_variable_ =
    transport->wait_strategy ()->leader_follower_condition_variable ();
}

void
TAO_Synch_Reply_Dispatcher::connection_closed (void)
{
  if (this->wait_strategy_ != 0)
    {
      this->wait_strategy_->connection_closed (
                                this->reply_received_,
                                this->leader_follower_condition_variable_
                              );
    }
}
