// $Id: Time_Policy_T.cpp 95332 2011-12-15 11:09:41Z mcorino $

#ifndef ACE_TIME_POLICY_T_CPP
#define ACE_TIME_POLICY_T_CPP

#include "ace/Time_Policy_T.h"

#if !defined (__ACE_INLINE__)
#include "ace/Time_Policy_T.inl"
#endif /* __ACE_INLINE__ */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template <typename TIME_POLICY> ACE_INLINE
ACE_Time_Policy_T<TIME_POLICY>::~ACE_Time_Policy_T ()
{
}

template <typename TIME_POLICY> ACE_INLINE ACE_Time_Value
ACE_Time_Policy_T<TIME_POLICY>::gettimeofday () const
{
  return this->time_policy_ ();
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_TIME_POLICY_T_CPP */
