#ifndef RS_GXS_RECOG_ITEMS_H
#define RS_GXS_RECOG_ITEMS_H

/*
 * libretroshare/src/serialiser: rsgxsrecogitems.h
 *
 * RetroShare Serialiser.
 *
 * Copyright 2013-2013 by Robert Fernie.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare@lunamutt.com".
 *
 */

#include <map>

#include "serialiser/rsserviceids.h"
#include "serialiser/rsserial.h"
#include "serialiser/rstlvkeys.h"
#include "serialiser/rstlvidset.h"

#if 0
#include "serialiser/rstlvbase.h"
#include "serialiser/rstlvtypes.h"

#endif

#include "retroshare/rsgxsifacetypes.h"

/**************************************************************************/

#define	RS_PKT_SUBTYPE_RECOGN_REQ	0x01
#define	RS_PKT_SUBTYPE_RECOGN_TAG	0x02
#define	RS_PKT_SUBTYPE_RECOGN_SIGNER	0x03


class RsGxsRecognReqItem: public RsItem
{
	public:
	RsGxsRecognReqItem() 
	:RsItem(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_GXS_RECOGN, 
		RS_PKT_SUBTYPE_RECOGN_REQ)
	{ 
		setPriorityLevel(QOS_PRIORITY_DEFAULT);
		return; 
	}
virtual ~RsGxsRecognReqItem();
virtual void clear();  
std::ostream &print(std::ostream &out, uint16_t indent = 0);


	uint32_t issued_at;
	uint32_t period;
	uint16_t tag_class;
	uint16_t tag_type;

	RsGxsId identity;
	std::string nickname;
	std::string comment;

	RsTlvKeySignature sign;
};


class RsGxsRecognTagItem: public RsItem
{
	public:
	RsGxsRecognTagItem() 
	:RsItem(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_GXS_RECOGN, 
		RS_PKT_SUBTYPE_RECOGN_TAG)
	{ 
		setPriorityLevel(QOS_PRIORITY_DEFAULT);
		return; 
	}
virtual ~RsGxsRecognTagItem();
virtual void clear();  
std::ostream &print(std::ostream &out, uint16_t indent = 0);

	uint32_t valid_from;
	uint32_t valid_to;
	uint16_t tag_class;
	uint16_t tag_type;

	RsGxsId identity;
	std::string nickname;

	RsTlvKeySignature sign;
};


class RsGxsRecognSignerItem: public RsItem
{
	public:
	RsGxsRecognSignerItem() 
	:RsItem(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_GXS_RECOGN, 
		RS_PKT_SUBTYPE_RECOGN_SIGNER)
	{ 
		setPriorityLevel(QOS_PRIORITY_DEFAULT);
		return; 
	}
virtual ~RsGxsRecognSignerItem();
virtual void clear();  
std::ostream &print(std::ostream &out, uint16_t indent = 0);

	RsTlvServiceIdSet signing_classes;
	RsTlvPublicRSAKey  key; // has from->to, and flags.
	RsTlvKeySignature sign;
};


class RsGxsRecognSerialiser: public RsSerialType
{
	public:
	RsGxsRecognSerialiser()
	:RsSerialType(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_GXS_RECOGN)
	{ return; }
virtual     ~RsGxsRecognSerialiser()
	{ return; }

	
virtual	uint32_t    size(RsItem *);
virtual	bool        serialise  (RsItem *item, void *data, uint32_t *size);
virtual	RsItem *    deserialise(void *data, uint32_t *size);

	private:

virtual	uint32_t    sizeReq(RsGxsRecognReqItem *);
virtual	bool        serialiseReq(RsGxsRecognReqItem *item, void *data, uint32_t *size);
virtual	RsGxsRecognReqItem *deserialiseReq(void *data, uint32_t *size);	
	
virtual	uint32_t    sizeTag(RsGxsRecognTagItem *);
virtual	bool        serialiseTag(RsGxsRecognTagItem *item, void *data, uint32_t *size);
virtual	RsGxsRecognTagItem *deserialiseTag(void *data, uint32_t *size);

virtual	uint32_t    sizeSigner(RsGxsRecognSignerItem *);
virtual	bool        serialiseSigner(RsGxsRecognSignerItem *item, void *data, uint32_t *size);
virtual	RsGxsRecognSignerItem *deserialiseSigner(void *data, uint32_t *size);

};

/**************************************************************************/

#endif /* RS_GXS_RECOGN_ITEMS_H */


