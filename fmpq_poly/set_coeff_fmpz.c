/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2010 William Hart

******************************************************************************/

#include <gmp.h>
#include <stdlib.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"

void fmpq_poly_set_coeff_fmpz(fmpq_poly_t poly, long n, const fmpz_t x)
{
    long len = poly->length;
    const int replace = (n < len && !fmpz_is_zero(poly->coeffs + n));
    
    if (!replace && fmpz_is_zero(x))
        return;
    
    if (n + 1 > len)
    {
        fmpq_poly_fit_length(poly, n + 1);
        _fmpq_poly_set_length(poly, n + 1);
        flint_mpn_zero((mp_ptr) poly->coeffs + len, (n + 1) - len);
    }
    
    if (*poly->den == 1L)
    {
        fmpz_set(poly->coeffs + n, x);
        if (replace)
            _fmpq_poly_normalise(poly);
    }
    else
    {
        fmpz_mul(poly->coeffs + n, poly->den, x);
        if (replace)
            fmpq_poly_canonicalise(poly);
    }
}

