// This file is part of Glest <https://github.com/Glest>
//
// Copyright (C) 2018  The Glest team
//
// Glest is a fork of MegaGlest <https://megaglest.org/>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>


#ifndef UTF8_FOR_CPP_UNCHECKED_H
#define UTF8_FOR_CPP_UNCHECKED_H

#include "core.h"

namespace utf8
{
    namespace unchecked 
    {
        template <typename octet_iterator>
        octet_iterator append(uint32_t cp, octet_iterator result)
        {
            if (cp < 0x80)                        // one octet
                *(result++) = static_cast<uint8_t>(cp);  
            else if (cp < 0x800) {                // two octets
                *(result++) = static_cast<uint8_t>((cp >> 6)          | 0xc0);
                *(result++) = static_cast<uint8_t>((cp & 0x3f)        | 0x80);
            }
            else if (cp < 0x10000) {              // three octets
                *(result++) = static_cast<uint8_t>((cp >> 12)         | 0xe0);
                *(result++) = static_cast<uint8_t>(((cp >> 6) & 0x3f) | 0x80);
                *(result++) = static_cast<uint8_t>((cp & 0x3f)        | 0x80);
            }
            else {                                // four octets
                *(result++) = static_cast<uint8_t>((cp >> 18)         | 0xf0);
                *(result++) = static_cast<uint8_t>(((cp >> 12) & 0x3f)| 0x80);
                *(result++) = static_cast<uint8_t>(((cp >> 6) & 0x3f) | 0x80);
                *(result++) = static_cast<uint8_t>((cp & 0x3f)        | 0x80);
            }
            return result;
        }

        template <typename octet_iterator>
        uint32_t next(octet_iterator& it)
        {
            uint32_t cp = internal::mask8(*it);
            typename std::iterator_traits<octet_iterator>::difference_type length = utf8::internal::sequence_length(it);
            switch (length) {
                case 1:
                    break;
                case 2:
                    it++;
                    cp = ((cp << 6) & 0x7ff) + ((*it) & 0x3f);
                    break;
                case 3:
                    ++it; 
                    cp = ((cp << 12) & 0xffff) + ((internal::mask8(*it) << 6) & 0xfff);
                    ++it;
                    cp += (*it) & 0x3f;
                    break;
                case 4:
                    ++it;
                    cp = ((cp << 18) & 0x1fffff) + ((internal::mask8(*it) << 12) & 0x3ffff);                
                    ++it;
                    cp += (internal::mask8(*it) << 6) & 0xfff;
                    ++it;
                    cp += (*it) & 0x3f; 
                    break;
            }
            ++it;
            return cp;        
        }

        template <typename octet_iterator>
        uint32_t peek_next(octet_iterator it)
        {
            return next(it);    
        }

        template <typename octet_iterator>
        uint32_t prior(octet_iterator& it)
        {
            while (internal::is_trail(*(--it))) ;
            octet_iterator temp = it;
            return next(temp);
        }

        // Deprecated in versions that include prior, but only for the sake of consistency (see utf8::previous)
        template <typename octet_iterator>
        inline uint32_t previous(octet_iterator& it)
        {
            return prior(it);
        }

        template <typename octet_iterator, typename distance_type>
        void advance (octet_iterator& it, distance_type n)
        {
            for (distance_type i = 0; i < n; ++i)
                next(it);
        }

        template <typename octet_iterator>
        typename std::iterator_traits<octet_iterator>::difference_type
        distance (octet_iterator first, octet_iterator last)
        {
            typename std::iterator_traits<octet_iterator>::difference_type dist;
            for (dist = 0; first < last; ++dist) 
                next(first);
            return dist;
        }

        template <typename u16bit_iterator, typename octet_iterator>
        octet_iterator utf16to8 (u16bit_iterator start, u16bit_iterator end, octet_iterator result)
        {       
            while (start != end) {
                uint32_t cp = internal::mask16(*start++);
            // Take care of surrogate pairs first
                if (internal::is_lead_surrogate(cp)) {
                    uint32_t trail_surrogate = internal::mask16(*start++);
                    cp = (cp << 10) + trail_surrogate + internal::SURROGATE_OFFSET;
                }
                result = append(cp, result);
            }
            return result;         
        }

        template <typename u16bit_iterator, typename octet_iterator>
        u16bit_iterator utf8to16 (octet_iterator start, octet_iterator end, u16bit_iterator result)
        {
            while (start < end) {
                uint32_t cp = next(start);
                if (cp > 0xffff) { //make a surrogate pair
                    *result++ = static_cast<uint16_t>((cp >> 10)   + internal::LEAD_OFFSET);
                    *result++ = static_cast<uint16_t>((cp & 0x3ff) + internal::TRAIL_SURROGATE_MIN);
                }
                else
                    *result++ = static_cast<uint16_t>(cp);
            }
            return result;
        }

        template <typename octet_iterator, typename u32bit_iterator>
        octet_iterator utf32to8 (u32bit_iterator start, u32bit_iterator end, octet_iterator result)
        {
            while (start != end)
                result = append(*(start++), result);

            return result;
        }

        template <typename octet_iterator, typename u32bit_iterator>
        u32bit_iterator utf8to32 (octet_iterator start, octet_iterator end, u32bit_iterator result)
        {
            while (start < end)
                (*result++) = next(start);

            return result;
        }

        // The iterator class
        template <typename octet_iterator>
          class iterator : public std::iterator <std::bidirectional_iterator_tag, uint32_t> { 
            octet_iterator it;
            public:
            iterator () {};
            explicit iterator (const octet_iterator& octet_it): it(octet_it) {}
            // the default "big three" are OK
            octet_iterator base () const { return it; }
            uint32_t operator * () const
            {
                octet_iterator temp = it;
                return next(temp);
            }
            bool operator == (const iterator& rhs) const 
            { 
                return (it == rhs.it);
            }
            bool operator != (const iterator& rhs) const
            {
                return !(operator == (rhs));
            }
            iterator& operator ++ () 
            {
                std::advance(it, internal::sequence_length(it));
                return *this;
            }
            iterator operator ++ (int)
            {
                iterator temp = *this;
                std::advance(it, internal::sequence_length(it));
                return temp;
            }  
            iterator& operator -- ()
            {
                prior(it);
                return *this;
            }
            iterator operator -- (int)
            {
                iterator temp = *this;
                prior(it);
                return temp;
            }
          }; // class iterator

    } // namespace utf8::unchecked
} // namespace utf8 


#endif // header guard
