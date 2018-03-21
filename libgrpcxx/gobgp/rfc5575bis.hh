
#pragma once

// From https://tools.ietf.org/html/draft-ietf-idr-rfc5575bis-06#section-4.2.3
/*
 *     0   1   2   3   4   5   6   7
 *   +---+---+---+---+---+---+---+---+
 *   | e | a |  len  | 0 |lt |gt |eq |
 *   +---+---+---+---+---+---+---+---+
 *
 *        Numeric operator
 *
 *      e - end-of-list bit.  Set in the last {op, value} pair in the
 *      list.
 *
 *      a - AND bit.  If unset, the previous term is logically ORed with
 *      the current one.  If set, the operation is a logical AND.  It
 *      should be unset in the first operator byte of a sequence.  The AND
 *      operator has higher priority than OR for the purposes of
 *      evaluating logical expressions.
 *
 *      len - length of the value field for this operand encodes 1 (00) -
 *      4 (11) bytes.  Type 3 flow component values are always encoded as
 *      single byte (len = 00).
 *
 *      lt - less than comparison between data and value.
 *
 *      gt - greater than comparison between data and value.
 *
 *      eq - equality between data and value.
 */


static inline size_t numop_len (uint8_t op)
{
  return ((0x30 & op) >> 4)+1;
}

enum numop_numericop_type {
  TRUE,
  EQ,
  GT,
  GTE,
  LT,
  LTE,
  NEQ,
  FALSE,
};

static inline numop_numericop_type numop_type (uint8_t op)
{
  /*
   * +----+----+----+----------------------------------+
   * | lt | gt | eq | Resulting operation              |
   * +----+----+----+----------------------------------+
   * | 0  | 0  | 0  | true (independent of the value)  |
   * | 0  | 0  | 1  | == (equal)                       |
   * | 0  | 1  | 0  | > (greater than)                 |
   * | 0  | 1  | 1  | >= (greater than or equal)       |
   * | 1  | 0  | 0  | < (less than)                    |
   * | 1  | 0  | 1  | <= (less than or equal)          |
   * | 1  | 1  | 0  | != (not equal value)             |
   * | 1  | 1  | 1  | false (independent of the value) |
   * +----+----+----+----------------------------------+
   */
  bool lt = (0x04 & op) != 0;
  bool gt = (0x02 & op) != 0;
  bool eq = (0x01 & op) != 0;
  if      (!lt &&  gt &&  eq) return TRUE;
  else if ( lt &&  gt && !eq) return EQ;
  else if ( lt && !gt &&  eq) return GT;
  else if ( lt && !gt && !eq) return GTE;
  else if (!lt &&  gt &&  eq) return LT;
  else if (!lt &&  gt && !eq) return LTE;
  else if (!lt && !gt &&  eq) return NEQ;
  else if (!lt && !gt && !eq) return FALSE;
  else assert (false);
}


