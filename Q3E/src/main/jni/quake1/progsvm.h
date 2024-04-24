/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
/*
This is a try to make the vm more generic, it is mainly based on the progs.h file.
For the license refer to progs.h.

Generic means, less as possible hard-coded links with the other parts of the engine.
This means no edict_engineprivate struct usage, etc.
The code uses void pointers instead.
*/

#ifndef PROGSVM_H
#define PROGSVM_H

#include <stddef.h>
#include "qtypes.h"
#include "qdefs.h"
#include "common.h"
#include "zone.h"
#include "pr_comp.h"			// defs shared with qcc
#include "progdefs.h"			// generated by program cdefs
#include "clprogdefs.h"			// generated by program cdefs

struct framegroupblend_s;
struct frameblend_s;
struct cmd_state_s;
struct qfile_s;

#ifndef DP_SMALLMEMORY
#define PROFILING
#endif

typedef struct prvm_stack_s
{
	int				s;
	mfunction_t		*f;
	double			tprofile_acc;
	double			profile_acc;
	double			builtinsprofile_acc;
} prvm_stack_t;


typedef union prvm_eval_s
{
	prvm_int_t		string;
	prvm_vec_t	_float;
	prvm_vec_t	vector[3];
	prvm_int_t		function;
	prvm_int_t		ivector[3];
	prvm_int_t		_int;
	prvm_int_t		edict;
} prvm_eval_t;

typedef struct prvm_required_field_s
{
	int type;
	const char *name;
} prvm_required_field_t;

#define PRVM_EDICT_MARK_WAIT_FOR_SETORIGIN -1
#define PRVM_EDICT_MARK_SETORIGIN_CAUGHT -2
// AK: I dont call it engine private cause it doesnt really belongs to the engine
//     it belongs to prvm.
typedef struct prvm_edict_private_s
{
	// mark for the leak detector
	int mark;
	// place in the code where it was allocated (for the leak detector)
	const char *allocation_origin;
} prvm_edict_private_t;

typedef struct prvm_edict_s
{
	// true if this edict is unused
	qbool free;
	// sv.time when the object was freed (to prevent early reuse which could
	// mess up client interpolation or obscure severe QuakeC bugs)
	double freetime;

	// engine-private fields (stored in dynamically resized array)
	union
	{
		prvm_edict_private_t *required;
		prvm_vec_t *fp;
		prvm_int_t *ip;
		// FIXME: this server pointer really means world, not server
		// (it is used by both server qc and client qc, but not menu qc)
		struct edict_engineprivate_s *server;
		// add other private structs as you desire
		// new structs have to start with the elements of prvm_edit_private_t
		// e.g. a new struct has to either look like this:
		//	typedef struct server_edict_private_s {
		//		prvm_edict_private_t base;
		//		vec3_t moved_from;
		//      vec3_t moved_fromangles;
		//		... } server_edict_private_t;
		// or:
		//	typedef struct server_edict_private_s {
		//		qbool free;
		//		float freetime;
		//		vec3_t moved_from;
		//      vec3_t moved_fromangles;
		//		... } server_edict_private_t;
		// However, the first one should be preferred.
	} priv;
	// QuakeC fields (stored in dynamically resized array)
	union
	{
		prvm_vec_t *fp;
		prvm_int_t *ip;
//		entvars_t		*server;
//		cl_entvars_t	*client;
	} fields;
} prvm_edict_t;

extern prvm_eval_t prvm_badvalue;

#define PRVM_alledictfloat(ed, fieldname)    (PRVM_EDICTFIELDFLOAT(ed, prog->fieldoffsets.fieldname))
#define PRVM_alledictvector(ed, fieldname)   (PRVM_EDICTFIELDVECTOR(ed, prog->fieldoffsets.fieldname))
#define PRVM_alledictstring(ed, fieldname)   (PRVM_EDICTFIELDSTRING(ed, prog->fieldoffsets.fieldname))
#define PRVM_alledictedict(ed, fieldname)    (PRVM_EDICTFIELDEDICT(ed, prog->fieldoffsets.fieldname))
#define PRVM_alledictfunction(ed, fieldname) (PRVM_EDICTFIELDFUNCTION(ed, prog->fieldoffsets.fieldname))
#define PRVM_allglobalfloat(fieldname)       (PRVM_GLOBALFIELDFLOAT(prog->globaloffsets.fieldname))
#define PRVM_allglobalvector(fieldname)      (PRVM_GLOBALFIELDVECTOR(prog->globaloffsets.fieldname))
#define PRVM_allglobalstring(fieldname)      (PRVM_GLOBALFIELDSTRING(prog->globaloffsets.fieldname))
#define PRVM_allglobaledict(fieldname)       (PRVM_GLOBALFIELDEDICT(prog->globaloffsets.fieldname))
#define PRVM_allglobalfunction(fieldname)    (PRVM_GLOBALFIELDFUNCTION(prog->globaloffsets.fieldname))
#define PRVM_allfunction(funcname)           (prog->funcoffsets.funcname)

#define PRVM_drawedictfloat(ed, fieldname)    (PRVM_EDICTFIELDFLOAT(ed, prog->fieldoffsets.fieldname))
#define PRVM_drawedictvector(ed, fieldname)   (PRVM_EDICTFIELDVECTOR(ed, prog->fieldoffsets.fieldname))
#define PRVM_drawedictstring(ed, fieldname)   (PRVM_EDICTFIELDSTRING(ed, prog->fieldoffsets.fieldname))
#define PRVM_drawedictedict(ed, fieldname)    (PRVM_EDICTFIELDEDICT(ed, prog->fieldoffsets.fieldname))
#define PRVM_drawedictfunction(ed, fieldname) (PRVM_EDICTFIELDFUNCTION(ed, prog->fieldoffsets.fieldname))
#define PRVM_drawglobalfloat(fieldname)       (PRVM_GLOBALFIELDFLOAT(prog->globaloffsets.fieldname))
#define PRVM_drawglobalvector(fieldname)      (PRVM_GLOBALFIELDVECTOR(prog->globaloffsets.fieldname))
#define PRVM_drawglobalstring(fieldname)      (PRVM_GLOBALFIELDSTRING(prog->globaloffsets.fieldname))
#define PRVM_drawglobaledict(fieldname)       (PRVM_GLOBALFIELDEDICT(prog->globaloffsets.fieldname))
#define PRVM_drawglobalfunction(fieldname)    (PRVM_GLOBALFIELDFUNCTION(prog->globaloffsets.fieldname))
#define PRVM_drawfunction(funcname)           (prog->funcoffsets.funcname)

#define PRVM_gameedictfloat(ed, fieldname)    (PRVM_EDICTFIELDFLOAT(ed, prog->fieldoffsets.fieldname))
#define PRVM_gameedictvector(ed, fieldname)   (PRVM_EDICTFIELDVECTOR(ed, prog->fieldoffsets.fieldname))
#define PRVM_gameedictstring(ed, fieldname)   (PRVM_EDICTFIELDSTRING(ed, prog->fieldoffsets.fieldname))
#define PRVM_gameedictedict(ed, fieldname)    (PRVM_EDICTFIELDEDICT(ed, prog->fieldoffsets.fieldname))
#define PRVM_gameedictfunction(ed, fieldname) (PRVM_EDICTFIELDFUNCTION(ed, prog->fieldoffsets.fieldname))
#define PRVM_gameglobalfloat(fieldname)       (PRVM_GLOBALFIELDFLOAT(prog->globaloffsets.fieldname))
#define PRVM_gameglobalvector(fieldname)      (PRVM_GLOBALFIELDVECTOR(prog->globaloffsets.fieldname))
#define PRVM_gameglobalstring(fieldname)      (PRVM_GLOBALFIELDSTRING(prog->globaloffsets.fieldname))
#define PRVM_gameglobaledict(fieldname)       (PRVM_GLOBALFIELDEDICT(prog->globaloffsets.fieldname))
#define PRVM_gameglobalfunction(fieldname)    (PRVM_GLOBALFIELDFUNCTION(prog->globaloffsets.fieldname))
#define PRVM_gamefunction(funcname)           (prog->funcoffsets.funcname)

#define PRVM_serveredictfloat(ed, fieldname)    (PRVM_EDICTFIELDFLOAT(ed, prog->fieldoffsets.fieldname))
#define PRVM_serveredictvector(ed, fieldname)   (PRVM_EDICTFIELDVECTOR(ed, prog->fieldoffsets.fieldname))
#define PRVM_serveredictstring(ed, fieldname)   (PRVM_EDICTFIELDSTRING(ed, prog->fieldoffsets.fieldname))
#define PRVM_serveredictedict(ed, fieldname)    (PRVM_EDICTFIELDEDICT(ed, prog->fieldoffsets.fieldname))
#define PRVM_serveredictfunction(ed, fieldname) (PRVM_EDICTFIELDFUNCTION(ed, prog->fieldoffsets.fieldname))
#define PRVM_serverglobalfloat(fieldname)       (PRVM_GLOBALFIELDFLOAT(prog->globaloffsets.fieldname))
#define PRVM_serverglobalvector(fieldname)      (PRVM_GLOBALFIELDVECTOR(prog->globaloffsets.fieldname))
#define PRVM_serverglobalstring(fieldname)      (PRVM_GLOBALFIELDSTRING(prog->globaloffsets.fieldname))
#define PRVM_serverglobaledict(fieldname)       (PRVM_GLOBALFIELDEDICT(prog->globaloffsets.fieldname))
#define PRVM_serverglobalfunction(fieldname)    (PRVM_GLOBALFIELDFUNCTION(prog->globaloffsets.fieldname))
#define PRVM_serverfunction(funcname)           (prog->funcoffsets.funcname)

#define PRVM_clientedictfloat(ed, fieldname)    (PRVM_EDICTFIELDFLOAT(ed, prog->fieldoffsets.fieldname))
#define PRVM_clientedictvector(ed, fieldname)   (PRVM_EDICTFIELDVECTOR(ed, prog->fieldoffsets.fieldname))
#define PRVM_clientedictstring(ed, fieldname)   (PRVM_EDICTFIELDSTRING(ed, prog->fieldoffsets.fieldname))
#define PRVM_clientedictedict(ed, fieldname)    (PRVM_EDICTFIELDEDICT(ed, prog->fieldoffsets.fieldname))
#define PRVM_clientedictfunction(ed, fieldname) (PRVM_EDICTFIELDFUNCTION(ed, prog->fieldoffsets.fieldname))
#define PRVM_clientglobalfloat(fieldname)       (PRVM_GLOBALFIELDFLOAT(prog->globaloffsets.fieldname))
#define PRVM_clientglobalvector(fieldname)      (PRVM_GLOBALFIELDVECTOR(prog->globaloffsets.fieldname))
#define PRVM_clientglobalstring(fieldname)      (PRVM_GLOBALFIELDSTRING(prog->globaloffsets.fieldname))
#define PRVM_clientglobaledict(fieldname)       (PRVM_GLOBALFIELDEDICT(prog->globaloffsets.fieldname))
#define PRVM_clientglobalfunction(fieldname)    (PRVM_GLOBALFIELDFUNCTION(prog->globaloffsets.fieldname))
#define PRVM_clientfunction(funcname)           (prog->funcoffsets.funcname)

#define PRVM_menuedictfloat(ed, fieldname)    (PRVM_EDICTFIELDFLOAT(ed, prog->fieldoffsets.fieldname))
#define PRVM_menuedictvector(ed, fieldname)   (PRVM_EDICTFIELDVECTOR(ed, prog->fieldoffsets.fieldname))
#define PRVM_menuedictstring(ed, fieldname)   (PRVM_EDICTFIELDSTRING(ed, prog->fieldoffsets.fieldname))
#define PRVM_menuedictedict(ed, fieldname)    (PRVM_EDICTFIELDEDICT(ed, prog->fieldoffsets.fieldname))
#define PRVM_menuedictfunction(ed, fieldname) (PRVM_EDICTFIELDFUNCTION(ed, prog->fieldoffsets.fieldname))
#define PRVM_menuglobalfloat(fieldname)       (PRVM_GLOBALFIELDFLOAT(prog->globaloffsets.fieldname))
#define PRVM_menuglobalvector(fieldname)      (PRVM_GLOBALFIELDVECTOR(prog->globaloffsets.fieldname))
#define PRVM_menuglobalstring(fieldname)      (PRVM_GLOBALFIELDSTRING(prog->globaloffsets.fieldname))
#define PRVM_menuglobaledict(fieldname)       (PRVM_GLOBALFIELDEDICT(prog->globaloffsets.fieldname))
#define PRVM_menuglobalfunction(fieldname)    (PRVM_GLOBALFIELDFUNCTION(prog->globaloffsets.fieldname))
#define PRVM_menufunction(funcname)           (prog->funcoffsets.funcname)

#if 1
#define PRVM_EDICTFIELDVALUE(ed, fieldoffset)    ((fieldoffset) < 0 ? Con_Printf("Invalid fieldoffset at %s:%i\n", __FILE__, __LINE__), &prvm_badvalue : (prvm_eval_t *)((ed)->fields.fp + (fieldoffset)))
#define PRVM_EDICTFIELDFLOAT(ed, fieldoffset)    (PRVM_EDICTFIELDVALUE(ed, fieldoffset)->_float)
#define PRVM_EDICTFIELDVECTOR(ed, fieldoffset)   (PRVM_EDICTFIELDVALUE(ed, fieldoffset)->vector)
#define PRVM_EDICTFIELDSTRING(ed, fieldoffset)   (PRVM_EDICTFIELDVALUE(ed, fieldoffset)->string)
#define PRVM_EDICTFIELDEDICT(ed, fieldoffset)    (PRVM_EDICTFIELDVALUE(ed, fieldoffset)->edict)
#define PRVM_EDICTFIELDFUNCTION(ed, fieldoffset) (PRVM_EDICTFIELDVALUE(ed, fieldoffset)->function)
#define PRVM_GLOBALFIELDVALUE(fieldoffset)       ((fieldoffset) < 0 ? Con_Printf("Invalid fieldoffset at %s:%i\n", __FILE__, __LINE__), &prvm_badvalue : (prvm_eval_t *)(prog->globals.fp + (fieldoffset)))
#define PRVM_GLOBALFIELDFLOAT(fieldoffset)       (PRVM_GLOBALFIELDVALUE(fieldoffset)->_float)
#define PRVM_GLOBALFIELDVECTOR(fieldoffset)      (PRVM_GLOBALFIELDVALUE(fieldoffset)->vector)
#define PRVM_GLOBALFIELDSTRING(fieldoffset)      (PRVM_GLOBALFIELDVALUE(fieldoffset)->string)
#define PRVM_GLOBALFIELDEDICT(fieldoffset)       (PRVM_GLOBALFIELDVALUE(fieldoffset)->edict)
#define PRVM_GLOBALFIELDFUNCTION(fieldoffset)    (PRVM_GLOBALFIELDVALUE(fieldoffset)->function)
#else
#define PRVM_EDICTFIELDVALUE(ed, fieldoffset) ((prvm_eval_t *)(ed->fields.fp + fieldoffset))
#define PRVM_EDICTFIELDFLOAT(ed, fieldoffset) (((prvm_eval_t *)(ed->fields.fp + fieldoffset))->_float)
#define PRVM_EDICTFIELDVECTOR(ed, fieldoffset) (((prvm_eval_t *)(ed->fields.fp + fieldoffset))->vector)
#define PRVM_EDICTFIELDSTRING(ed, fieldoffset) (((prvm_eval_t *)(ed->fields.fp + fieldoffset))->string)
#define PRVM_EDICTFIELDEDICT(ed, fieldoffset) (((prvm_eval_t *)(ed->fields.fp + fieldoffset))->edict)
#define PRVM_EDICTFIELDFUNCTION(ed, fieldoffset) (((prvm_eval_t *)(ed->fields.fp + fieldoffset))->function)
#define PRVM_GLOBALFIELDVALUE(fieldoffset) ((prvm_eval_t *)(prog->globals.fp + fieldoffset))
#define PRVM_GLOBALFIELDFLOAT(fieldoffset) (((prvm_eval_t *)(prog->globals.fp + fieldoffset))->_float)
#define PRVM_GLOBALFIELDVECTOR(fieldoffset) (((prvm_eval_t *)(prog->globals.fp + fieldoffset))->vector)
#define PRVM_GLOBALFIELDSTRING(fieldoffset) (((prvm_eval_t *)(prog->globals.fp + fieldoffset))->string)
#define PRVM_GLOBALFIELDEDICT(fieldoffset) (((prvm_eval_t *)(prog->globals.fp + fieldoffset))->edict)
#define PRVM_GLOBALFIELDFUNCTION(fieldoffset) (((prvm_eval_t *)(prog->globals.fp + fieldoffset))->function)
#endif

//============================================================================
// prog->flag
#define PRVM_OP_STATE       1
#define PRVM_CSQC_SIMPLE    2

#ifdef DP_SMALLMEMORY
#define	PRVM_MAX_STACK_DEPTH		128
#define	PRVM_LOCALSTACK_SIZE		2048

#define PRVM_MAX_OPENFILES 16
#define PRVM_MAX_OPENSEARCHES 8
#else
#define	PRVM_MAX_STACK_DEPTH		1024
#define	PRVM_LOCALSTACK_SIZE		16384

#define PRVM_MAX_OPENFILES 256
#define PRVM_MAX_OPENSEARCHES 128
#endif

struct prvm_prog_s;
typedef void (*prvm_builtin_t) (struct prvm_prog_s *prog);

// NOTE: field offsets use -1 for NULL
typedef struct prvm_prog_fieldoffsets_s
{
#define PRVM_DECLARE_serverglobalfloat(x)
#define PRVM_DECLARE_serverglobalvector(x)
#define PRVM_DECLARE_serverglobalstring(x)
#define PRVM_DECLARE_serverglobaledict(x)
#define PRVM_DECLARE_serverglobalfunction(x)
#define PRVM_DECLARE_clientglobalfloat(x)
#define PRVM_DECLARE_clientglobalvector(x)
#define PRVM_DECLARE_clientglobalstring(x)
#define PRVM_DECLARE_clientglobaledict(x)
#define PRVM_DECLARE_clientglobalfunction(x)
#define PRVM_DECLARE_menuglobalfloat(x)
#define PRVM_DECLARE_menuglobalvector(x)
#define PRVM_DECLARE_menuglobalstring(x)
#define PRVM_DECLARE_menuglobaledict(x)
#define PRVM_DECLARE_menuglobalfunction(x)
#define PRVM_DECLARE_serverfieldfloat(x)
#define PRVM_DECLARE_serverfieldvector(x)
#define PRVM_DECLARE_serverfieldstring(x)
#define PRVM_DECLARE_serverfieldedict(x)
#define PRVM_DECLARE_serverfieldfunction(x)
#define PRVM_DECLARE_clientfieldfloat(x)
#define PRVM_DECLARE_clientfieldvector(x)
#define PRVM_DECLARE_clientfieldstring(x)
#define PRVM_DECLARE_clientfieldedict(x)
#define PRVM_DECLARE_clientfieldfunction(x)
#define PRVM_DECLARE_menufieldfloat(x)
#define PRVM_DECLARE_menufieldvector(x)
#define PRVM_DECLARE_menufieldstring(x)
#define PRVM_DECLARE_menufieldedict(x)
#define PRVM_DECLARE_menufieldfunction(x)
#define PRVM_DECLARE_serverfunction(x)
#define PRVM_DECLARE_clientfunction(x)
#define PRVM_DECLARE_menufunction(x)
#define PRVM_DECLARE_field(x) int x;
#define PRVM_DECLARE_global(x)
#define PRVM_DECLARE_function(x)
#include "prvm_offsets.h"
#undef PRVM_DECLARE_serverglobalfloat
#undef PRVM_DECLARE_serverglobalvector
#undef PRVM_DECLARE_serverglobalstring
#undef PRVM_DECLARE_serverglobaledict
#undef PRVM_DECLARE_serverglobalfunction
#undef PRVM_DECLARE_clientglobalfloat
#undef PRVM_DECLARE_clientglobalvector
#undef PRVM_DECLARE_clientglobalstring
#undef PRVM_DECLARE_clientglobaledict
#undef PRVM_DECLARE_clientglobalfunction
#undef PRVM_DECLARE_menuglobalfloat
#undef PRVM_DECLARE_menuglobalvector
#undef PRVM_DECLARE_menuglobalstring
#undef PRVM_DECLARE_menuglobaledict
#undef PRVM_DECLARE_menuglobalfunction
#undef PRVM_DECLARE_serverfieldfloat
#undef PRVM_DECLARE_serverfieldvector
#undef PRVM_DECLARE_serverfieldstring
#undef PRVM_DECLARE_serverfieldedict
#undef PRVM_DECLARE_serverfieldfunction
#undef PRVM_DECLARE_clientfieldfloat
#undef PRVM_DECLARE_clientfieldvector
#undef PRVM_DECLARE_clientfieldstring
#undef PRVM_DECLARE_clientfieldedict
#undef PRVM_DECLARE_clientfieldfunction
#undef PRVM_DECLARE_menufieldfloat
#undef PRVM_DECLARE_menufieldvector
#undef PRVM_DECLARE_menufieldstring
#undef PRVM_DECLARE_menufieldedict
#undef PRVM_DECLARE_menufieldfunction
#undef PRVM_DECLARE_serverfunction
#undef PRVM_DECLARE_clientfunction
#undef PRVM_DECLARE_menufunction
#undef PRVM_DECLARE_field
#undef PRVM_DECLARE_global
#undef PRVM_DECLARE_function
}
prvm_prog_fieldoffsets_t;

// NOTE: global offsets use -1 for NULL
typedef struct prvm_prog_globaloffsets_s
{
#define PRVM_DECLARE_serverglobalfloat(x)
#define PRVM_DECLARE_serverglobalvector(x)
#define PRVM_DECLARE_serverglobalstring(x)
#define PRVM_DECLARE_serverglobaledict(x)
#define PRVM_DECLARE_serverglobalfunction(x)
#define PRVM_DECLARE_clientglobalfloat(x)
#define PRVM_DECLARE_clientglobalvector(x)
#define PRVM_DECLARE_clientglobalstring(x)
#define PRVM_DECLARE_clientglobaledict(x)
#define PRVM_DECLARE_clientglobalfunction(x)
#define PRVM_DECLARE_menuglobalfloat(x)
#define PRVM_DECLARE_menuglobalvector(x)
#define PRVM_DECLARE_menuglobalstring(x)
#define PRVM_DECLARE_menuglobaledict(x)
#define PRVM_DECLARE_menuglobalfunction(x)
#define PRVM_DECLARE_serverfieldfloat(x)
#define PRVM_DECLARE_serverfieldvector(x)
#define PRVM_DECLARE_serverfieldstring(x)
#define PRVM_DECLARE_serverfieldedict(x)
#define PRVM_DECLARE_serverfieldfunction(x)
#define PRVM_DECLARE_clientfieldfloat(x)
#define PRVM_DECLARE_clientfieldvector(x)
#define PRVM_DECLARE_clientfieldstring(x)
#define PRVM_DECLARE_clientfieldedict(x)
#define PRVM_DECLARE_clientfieldfunction(x)
#define PRVM_DECLARE_menufieldfloat(x)
#define PRVM_DECLARE_menufieldvector(x)
#define PRVM_DECLARE_menufieldstring(x)
#define PRVM_DECLARE_menufieldedict(x)
#define PRVM_DECLARE_menufieldfunction(x)
#define PRVM_DECLARE_serverfunction(x)
#define PRVM_DECLARE_clientfunction(x)
#define PRVM_DECLARE_menufunction(x)
#define PRVM_DECLARE_field(x)
#define PRVM_DECLARE_global(x) int x;
#define PRVM_DECLARE_function(x)
#include "prvm_offsets.h"
#undef PRVM_DECLARE_serverglobalfloat
#undef PRVM_DECLARE_serverglobalvector
#undef PRVM_DECLARE_serverglobalstring
#undef PRVM_DECLARE_serverglobaledict
#undef PRVM_DECLARE_serverglobalfunction
#undef PRVM_DECLARE_clientglobalfloat
#undef PRVM_DECLARE_clientglobalvector
#undef PRVM_DECLARE_clientglobalstring
#undef PRVM_DECLARE_clientglobaledict
#undef PRVM_DECLARE_clientglobalfunction
#undef PRVM_DECLARE_menuglobalfloat
#undef PRVM_DECLARE_menuglobalvector
#undef PRVM_DECLARE_menuglobalstring
#undef PRVM_DECLARE_menuglobaledict
#undef PRVM_DECLARE_menuglobalfunction
#undef PRVM_DECLARE_serverfieldfloat
#undef PRVM_DECLARE_serverfieldvector
#undef PRVM_DECLARE_serverfieldstring
#undef PRVM_DECLARE_serverfieldedict
#undef PRVM_DECLARE_serverfieldfunction
#undef PRVM_DECLARE_clientfieldfloat
#undef PRVM_DECLARE_clientfieldvector
#undef PRVM_DECLARE_clientfieldstring
#undef PRVM_DECLARE_clientfieldedict
#undef PRVM_DECLARE_clientfieldfunction
#undef PRVM_DECLARE_menufieldfloat
#undef PRVM_DECLARE_menufieldvector
#undef PRVM_DECLARE_menufieldstring
#undef PRVM_DECLARE_menufieldedict
#undef PRVM_DECLARE_menufieldfunction
#undef PRVM_DECLARE_serverfunction
#undef PRVM_DECLARE_clientfunction
#undef PRVM_DECLARE_menufunction
#undef PRVM_DECLARE_field
#undef PRVM_DECLARE_global
#undef PRVM_DECLARE_function
}
prvm_prog_globaloffsets_t;

// NOTE: function offsets use 0 for NULL
typedef struct prvm_prog_funcoffsets_s
{
#define PRVM_DECLARE_serverglobalfloat(x)
#define PRVM_DECLARE_serverglobalvector(x)
#define PRVM_DECLARE_serverglobalstring(x)
#define PRVM_DECLARE_serverglobaledict(x)
#define PRVM_DECLARE_serverglobalfunction(x)
#define PRVM_DECLARE_clientglobalfloat(x)
#define PRVM_DECLARE_clientglobalvector(x)
#define PRVM_DECLARE_clientglobalstring(x)
#define PRVM_DECLARE_clientglobaledict(x)
#define PRVM_DECLARE_clientglobalfunction(x)
#define PRVM_DECLARE_menuglobalfloat(x)
#define PRVM_DECLARE_menuglobalvector(x)
#define PRVM_DECLARE_menuglobalstring(x)
#define PRVM_DECLARE_menuglobaledict(x)
#define PRVM_DECLARE_menuglobalfunction(x)
#define PRVM_DECLARE_serverfieldfloat(x)
#define PRVM_DECLARE_serverfieldvector(x)
#define PRVM_DECLARE_serverfieldstring(x)
#define PRVM_DECLARE_serverfieldedict(x)
#define PRVM_DECLARE_serverfieldfunction(x)
#define PRVM_DECLARE_clientfieldfloat(x)
#define PRVM_DECLARE_clientfieldvector(x)
#define PRVM_DECLARE_clientfieldstring(x)
#define PRVM_DECLARE_clientfieldedict(x)
#define PRVM_DECLARE_clientfieldfunction(x)
#define PRVM_DECLARE_menufieldfloat(x)
#define PRVM_DECLARE_menufieldvector(x)
#define PRVM_DECLARE_menufieldstring(x)
#define PRVM_DECLARE_menufieldedict(x)
#define PRVM_DECLARE_menufieldfunction(x)
#define PRVM_DECLARE_serverfunction(x)
#define PRVM_DECLARE_clientfunction(x)
#define PRVM_DECLARE_menufunction(x)
#define PRVM_DECLARE_field(x)
#define PRVM_DECLARE_global(x)
#define PRVM_DECLARE_function(x) int x;
#include "prvm_offsets.h"
#undef PRVM_DECLARE_serverglobalfloat
#undef PRVM_DECLARE_serverglobalvector
#undef PRVM_DECLARE_serverglobalstring
#undef PRVM_DECLARE_serverglobaledict
#undef PRVM_DECLARE_serverglobalfunction
#undef PRVM_DECLARE_clientglobalfloat
#undef PRVM_DECLARE_clientglobalvector
#undef PRVM_DECLARE_clientglobalstring
#undef PRVM_DECLARE_clientglobaledict
#undef PRVM_DECLARE_clientglobalfunction
#undef PRVM_DECLARE_menuglobalfloat
#undef PRVM_DECLARE_menuglobalvector
#undef PRVM_DECLARE_menuglobalstring
#undef PRVM_DECLARE_menuglobaledict
#undef PRVM_DECLARE_menuglobalfunction
#undef PRVM_DECLARE_serverfieldfloat
#undef PRVM_DECLARE_serverfieldvector
#undef PRVM_DECLARE_serverfieldstring
#undef PRVM_DECLARE_serverfieldedict
#undef PRVM_DECLARE_serverfieldfunction
#undef PRVM_DECLARE_clientfieldfloat
#undef PRVM_DECLARE_clientfieldvector
#undef PRVM_DECLARE_clientfieldstring
#undef PRVM_DECLARE_clientfieldedict
#undef PRVM_DECLARE_clientfieldfunction
#undef PRVM_DECLARE_menufieldfloat
#undef PRVM_DECLARE_menufieldvector
#undef PRVM_DECLARE_menufieldstring
#undef PRVM_DECLARE_menufieldedict
#undef PRVM_DECLARE_menufieldfunction
#undef PRVM_DECLARE_serverfunction
#undef PRVM_DECLARE_clientfunction
#undef PRVM_DECLARE_menufunction
#undef PRVM_DECLARE_field
#undef PRVM_DECLARE_global
#undef PRVM_DECLARE_function
}
prvm_prog_funcoffsets_t;

// stringbuffer flags
#define STRINGBUFFER_SAVED     1   // saved in savegames
#define STRINGBUFFER_QCFLAGS   1   // allowed to be set by QC
#define STRINGBUFFER_TEMP      128 // internal use ONLY 
typedef struct prvm_stringbuffer_s
{
	int max_strings;
	int num_strings;
	char **strings;
	const char *origin;
	unsigned char flags;
}
prvm_stringbuffer_t;

// flags for knownstrings
#define KNOWNSTRINGFLAG_ENGINE 1
#define KNOWNSTRINGFLAG_GCMARK 2
#define KNOWNSTRINGFLAG_GCPRUNE 4 // cleared by GCMARK code, string is freed if prune remains after two sweeps

typedef enum prvm_prog_garbagecollection_state_stage_e
{
	PRVM_GC_START = 0,
	PRVM_GC_GLOBALS_MARK,
	PRVM_GC_FIELDS_MARK,
	PRVM_GC_KNOWNSTRINGS_SWEEP,
	PRVM_GC_RESET,
}
prvm_prog_garbagecollection_state_stage_t;

typedef struct prvm_prog_garbagecollection_state_s
{
	int stage;
	int globals_mark_progress;
	int fields_mark_progress;
	int fields_mark_progress_entity;
	int knownstrings_sweep_progress;
}
prvm_prog_garbagecollection_state_t;

// [INIT] variables flagged with this token can be initialized by 'you'
// NOTE: external code has to create and free the mempools but everything else is done by prvm !
typedef struct prvm_prog_s
{
	double				starttime; // system time when PRVM_Prog_Load was called
	double				inittime; // system time when QC initialization code finished (any entity created before is not a leak)
	double				profiletime; // system time when last PRVM_CallProfile was called (or PRVM_Prog_Load initially)
	mfunction_t			*functions;
	int				functions_covered;
	char				*strings;
	int					stringssize;
	mdef_t				*fielddefs;
	mdef_t				*globaldefs;
	mstatement_t		*statements;
	int					entityfields;			// number of vec_t fields in progs (some variables are 3)
	int					entityfieldsarea;		// LadyHavoc: equal to max_edicts * entityfields (for bounds checking)

	// loaded values from the disk format
	int					progs_version;
	int					progs_crc;
	int					progs_numstatements;
	int					progs_numglobaldefs;
	int					progs_numfielddefs;
	int					progs_numfunctions;
	int					progs_numstrings;
	int					progs_numglobals;
	int					progs_entityfields;

	// real values in memory (some modified by loader)
	int					numstatements;
	int					numglobaldefs;
	int					numfielddefs;
	int					numfunctions;
	int					numstrings;
	int					numglobals;

	int					*statement_linenums; // NULL if not available
	int					*statement_columnnums; // NULL if not available

	double				*statement_profile; // only incremented if prvm_statementprofiling is on
	int				statements_covered;
	double				*explicit_profile; // only incremented if prvm_statementprofiling is on
	int				explicit_covered;
	int				numexplicitcoveragestatements;

	union {
		prvm_vec_t *fp;
		prvm_int_t *ip;
//		globalvars_t *server;
//		cl_globalvars_t *client;
	} globals;

	int					maxknownstrings;
	int					numknownstrings;
	// this is updated whenever a string is removed or added
	// (simple optimization of the free string search)
	int					firstfreeknownstring;
	const char			**knownstrings;
	unsigned char		*knownstrings_flags;
	const char          **knownstrings_origin;
	const char			***stringshash;

	memexpandablearray_t	stringbuffersarray;

	// garbage collection status
	prvm_prog_garbagecollection_state_t gc;

	// all memory allocations related to this vm_prog (code, edicts, strings)
	mempool_t			*progs_mempool; // [INIT]

	prvm_builtin_t		*builtins; // [INIT]
	int					numbuiltins; // [INIT]

	int					argc;

	int					trace;
	int					break_statement;
	int					break_stack_index;
	int					watch_global;
	etype_t					watch_global_type;
	prvm_eval_t				watch_global_value;
	int					watch_edict;
	int					watch_field;
	etype_t					watch_field_type;
	prvm_eval_t				watch_edictfield_value;

	mfunction_t			*xfunction;
	int					xstatement;

	// stacktrace writes into stack[MAX_STACK_DEPTH]
	// thus increase the array, so depth wont be overwritten
	prvm_stack_t		stack[PRVM_MAX_STACK_DEPTH+1];
	int					depth;

	prvm_int_t			localstack[PRVM_LOCALSTACK_SIZE];
	int					localstack_used;

	unsigned short		filecrc;

	//============================================================================
	// until this point everything also exists (with the pr_ prefix) in the old vm

	struct qfile_s				*openfiles[PRVM_MAX_OPENFILES];
	const char *         openfiles_origin[PRVM_MAX_OPENFILES];
	struct fssearch_s			*opensearches[PRVM_MAX_OPENSEARCHES];
	const char *         opensearches_origin[PRVM_MAX_OPENSEARCHES];
	struct skeleton_s	*skeletons[MAX_EDICTS];
	struct cmd_state_s	*console_cmd; // points to the relevant console command interpreter for this vm (cmd_local or &cmd_server), also used to access cvars

	// buffer for storing all tempstrings created during one invocation of ExecuteProgram
	sizebuf_t			tempstringsbuf;

	// polygonbegin, polygonvertex, polygonend state
	// the polygon is buffered here until polygonend commits it to the relevant
	// CL_Mesh entity, because important decisions depend on the vertex data
	// provided (e.g. whether the polygon is transparent), we can't really do much
	// with it until we have all of the data...

	// this tracks the last polygonbegin's choice of
	// CL_Mesh_CSQC or CL_Mesh_UI for this polygon
	struct model_s		*polygonbegin_model;
	// indicates if polygonbegin should be interpreted as 2d
	// (clearscene sets this to false, renderscene sets this to true, drawpic
	//  also sets this to true)
	// note that in FTEQW polygonbegin with 2 args is handled very differently,
	// where the behavior is always 3D unless DRAWFLAG_2D is passed, but
	// DRAWFLAG_2D conflicts with our DRAWFLAG_SCREEN.
	qbool			polygonbegin_guess2d;
	// the texture name and drawflags provided to polygonbegin
	char				polygonbegin_texname[MAX_QPATH];
	int					polygonbegin_drawflags;
	// the vertex data
	int					polygonbegin_numvertices;
	int					polygonbegin_maxvertices;
	float				*polygonbegin_vertexdata;

	// copies of some vars that were former read from sv
	int					num_edicts;
	// number of edicts for which space has been (should be) allocated
	int					max_edicts; // [INIT]
	// used instead of the constant MAX_EDICTS
	int					limit_edicts; // [INIT]

	// number of reserved edicts (allocated from 1)
	int					reserved_edicts; // [INIT]

	prvm_edict_t		*edicts;
	union
	{
		prvm_vec_t *fp;
		prvm_int_t *ip;
	} edictsfields;
	void				*edictprivate;

	// size of the engine private struct
	int					edictprivate_size; // [INIT]

	prvm_prog_fieldoffsets_t	fieldoffsets;
	prvm_prog_globaloffsets_t	globaloffsets;
	prvm_prog_funcoffsets_t	funcoffsets;

	// allow writing to world entity fields, this is set by server init and
	// cleared before first server frame
	qbool			allowworldwrites;

	// name of the prog, e.g. "Server", "Client" or "Menu" (used for text output)
	const char			*name; // [INIT]

	// flag - used to store general flags like PRVM_GE_SELF, etc.
	unsigned			flag;

	const char			**extensionstring; // [INIT]

	qbool			loadintoworld; // [INIT]

	// used to indicate whether a prog is loaded
	qbool			loaded;
	qbool			leaktest_active;

	// translation buffer (only needs to be freed on unloading progs, type is private to prvm_edict.c)
	void *po;

	// printed together with backtraces
	const char *statestring;

	struct animatemodel_cache *animatemodel_cache;

//	prvm_builtin_mem_t  *mem_list;

// now passed as parameter of PRVM_Prog_Load
//	char				**required_func;
//	int					numrequiredfunc;

	//============================================================================

	mdef_t				*self; // if self != 0 then there is a global self

	//============================================================================
	// function pointers

	void				(*begin_increase_edicts)(struct prvm_prog_s *prog); // [INIT] used by PRVM_MEM_Increase_Edicts
	void				(*end_increase_edicts)(struct prvm_prog_s *prog); // [INIT]

	void				(*init_edict)(struct prvm_prog_s *prog, prvm_edict_t *edict); // [INIT] used by PRVM_ED_ClearEdict
	void				(*free_edict)(struct prvm_prog_s *prog, prvm_edict_t *ed); // [INIT] used by PRVM_ED_Free

	void				(*count_edicts)(struct prvm_prog_s *prog); // [INIT] used by PRVM_ED_Count_f

	qbool			(*load_edict)(struct prvm_prog_s *prog, prvm_edict_t *ent); // [INIT] used by PRVM_ED_LoadFromFile

	void				(*init_cmd)(struct prvm_prog_s *prog); // [INIT] used by PRVM_InitProg
	void				(*reset_cmd)(struct prvm_prog_s *prog); // [INIT] used by PRVM_ResetProg

	void				(*error_cmd)(const char *format, ...) DP_FUNC_PRINTF(1); // [INIT]

	void				(*ExecuteProgram)(struct prvm_prog_s *prog, func_t fnum, const char *errormessage); // pointer to one of the *VM_ExecuteProgram functions
} prvm_prog_t;

typedef enum prvm_progindex_e
{
	PRVM_PROG_SERVER,
	PRVM_PROG_CLIENT,
	PRVM_PROG_MENU,
	PRVM_PROG_MAX
}
prvm_progindex_t;

extern prvm_prog_t prvm_prog_list[PRVM_PROG_MAX];
prvm_prog_t *PRVM_ProgFromString(const char *str);
prvm_prog_t *PRVM_FriendlyProgFromString(const char *str); // for console commands (prints error if name unknown and returns NULL, prints error if prog not loaded and returns NULL)
#define PRVM_GetProg(n) (&prvm_prog_list[(n)])
#define PRVM_ProgLoaded(n) (PRVM_GetProg(n)->loaded)
#define SVVM_prog (&prvm_prog_list[PRVM_PROG_SERVER])
#define CLVM_prog (&prvm_prog_list[PRVM_PROG_CLIENT])
#ifdef CONFIG_MENU
#define MVM_prog (&prvm_prog_list[PRVM_PROG_MENU])
#endif

//============================================================================
// prvm_cmds part

extern prvm_builtin_t vm_sv_builtins[];
extern prvm_builtin_t vm_cl_builtins[];
extern prvm_builtin_t vm_m_builtins[];

extern const int vm_sv_numbuiltins;
extern const int vm_cl_numbuiltins;
extern const int vm_m_numbuiltins;

extern const char *vm_sv_extensions[]; // client also uses this
extern const char *vm_m_extensions[];

void SVVM_init_cmd(prvm_prog_t *prog);
void SVVM_reset_cmd(prvm_prog_t *prog);

void CLVM_init_cmd(prvm_prog_t *prog);
void CLVM_reset_cmd(prvm_prog_t *prog);

#ifdef CONFIG_MENU
void MVM_init_cmd(prvm_prog_t *prog);
void MVM_reset_cmd(prvm_prog_t *prog);
#endif

void VM_Cmd_Init(prvm_prog_t *prog);
void VM_Cmd_Reset(prvm_prog_t *prog);
//============================================================================

void PRVM_Init (void);

#ifdef PROFILING
void SVVM_ExecuteProgram (prvm_prog_t *prog, func_t fnum, const char *errormessage);
void CLVM_ExecuteProgram (prvm_prog_t *prog, func_t fnum, const char *errormessage);
#ifdef CONFIG_MENU
void MVM_ExecuteProgram (prvm_prog_t *prog, func_t fnum, const char *errormessage);
#endif
#else
#define SVVM_ExecuteProgram PRVM_ExecuteProgram
#define CLVM_ExecuteProgram PRVM_ExecuteProgram
#ifdef CONFIG_MENU
#define MVM_ExecuteProgram PRVM_ExecuteProgram
#endif
void PRVM_ExecuteProgram (prvm_prog_t *prog, func_t fnum, const char *errormessage);
#endif

#define PRVM_Alloc(buffersize) Mem_Alloc(prog->progs_mempool, buffersize)
#define PRVM_Free(buffer) Mem_Free(buffer)

void PRVM_Profile (prvm_prog_t *prog, int maxfunctions, double mintime, int sortby);
void PRVM_Profile_f(struct cmd_state_s *cmd);
void PRVM_ChildProfile_f(struct cmd_state_s *cmd);
void PRVM_CallProfile_f(struct cmd_state_s *cmd);
void PRVM_PrintFunction_f(struct cmd_state_s *cmd);

void PRVM_PrintState(prvm_prog_t *prog, int stack_index);
void PRVM_Crash(void);
void PRVM_ShortStackTrace(prvm_prog_t *prog, char *buf, size_t bufsize);
const char *PRVM_AllocationOrigin(prvm_prog_t *prog);
void PRVM_GarbageCollection(prvm_prog_t *prog);

mdef_t *PRVM_ED_FindField(prvm_prog_t *prog, const char *name);
mdef_t *PRVM_ED_FindGlobal(prvm_prog_t *prog, const char *name);
prvm_eval_t *PRVM_ED_FindGlobalEval(prvm_prog_t *prog, const char *name);
mfunction_t *PRVM_ED_FindFunction(prvm_prog_t *prog, const char *name);

int PRVM_ED_FindFieldOffset(prvm_prog_t *prog, const char *name);
int PRVM_ED_FindGlobalOffset(prvm_prog_t *prog, const char *name);
func_t PRVM_ED_FindFunctionOffset(prvm_prog_t *prog, const char *name);
#define PRVM_ED_FindFieldOffset_FromStruct(st, field) prog->fieldoffsets . field = ((int *)(&((st *)NULL)-> field ) - ((int *)NULL))
#define PRVM_ED_FindGlobalOffset_FromStruct(st, field) prog->globaloffsets . field = ((int *)(&((st *)NULL)-> field ) - ((int *)NULL))

void PRVM_MEM_IncreaseEdicts(prvm_prog_t *prog);

qbool PRVM_ED_CanAlloc(prvm_prog_t *prog, prvm_edict_t *e);
prvm_edict_t *PRVM_ED_Alloc(prvm_prog_t *prog);
void PRVM_ED_Free(prvm_prog_t *prog, prvm_edict_t *ed);
void PRVM_ED_ClearEdict(prvm_prog_t *prog, prvm_edict_t *e);

void PRVM_PrintFunctionStatements(prvm_prog_t *prog, const char *name);
void PRVM_ED_Print(prvm_prog_t *prog, prvm_edict_t *ed, const char *wildcard_fieldname);
void PRVM_ED_Write(prvm_prog_t *prog, struct qfile_s *f, prvm_edict_t *ed);
const char *PRVM_ED_ParseEdict(prvm_prog_t *prog, const char *data, prvm_edict_t *ent);

void PRVM_ED_WriteGlobals(prvm_prog_t *prog, struct qfile_s *f);
void PRVM_ED_ParseGlobals(prvm_prog_t *prog, const char *data);

void PRVM_ED_CallPrespawnFunction(prvm_prog_t *prog, prvm_edict_t *ent);
qbool PRVM_ED_CallSpawnFunction(prvm_prog_t *prog, prvm_edict_t *ent, const char *data, const char *start);
void PRVM_ED_CallPostspawnFunction (prvm_prog_t *prog, prvm_edict_t *ent);

void PRVM_ED_LoadFromFile(prvm_prog_t *prog, const char *data);

unsigned int PRVM_EDICT_NUM_ERROR(prvm_prog_t *prog, unsigned int n, const char *filename, int fileline);
#define PRVM_EDICT(n) (((unsigned)(n) < (unsigned int)prog->max_edicts) ? (unsigned int)(n) : PRVM_EDICT_NUM_ERROR(prog, (unsigned int)(n), __FILE__, __LINE__))
#define PRVM_EDICT_NUM(n) (prog->edicts + PRVM_EDICT(n))

//int NUM_FOR_EDICT_ERROR(prvm_edict_t *e);
#define PRVM_NUM_FOR_EDICT(e) ((int)((prvm_edict_t *)(e) - prog->edicts))
//int PRVM_NUM_FOR_EDICT(prvm_edict_t *e);

#define PRVM_NEXT_EDICT(e) ((e) + 1)

#define PRVM_EDICT_TO_PROG(e) (PRVM_NUM_FOR_EDICT(e))
//int PRVM_EDICT_TO_PROG(prvm_edict_t *e);
#define PRVM_PROG_TO_EDICT(n) (PRVM_EDICT_NUM(n))
//prvm_edict_t *PRVM_PROG_TO_EDICT(int n);

//============================================================================

#define PRVM_G_FLOAT(o) (prog->globals.fp[o])
#define PRVM_G_INT(o) (prog->globals.ip[o])
#define PRVM_G_EDICT(o) (PRVM_PROG_TO_EDICT(prog->globals.ip[o]))
#define PRVM_G_EDICTNUM(o) PRVM_NUM_FOR_EDICT(PRVM_G_EDICT(o))
#define PRVM_G_VECTOR(o) (&prog->globals.fp[o])
#define PRVM_G_STRING(o) (PRVM_GetString(prog, prog->globals.ip[o]))
//#define PRVM_G_FUNCTION(prog, o) (prog->globals.ip[o])

// FIXME: make these go away?
#define PRVM_E_FLOAT(e,o) (e->fields.fp[o])
#define PRVM_E_INT(e,o) (e->fields.ip[o])
//#define PRVM_E_VECTOR(e,o) (&(e->fields.fp[o]))
#define PRVM_E_STRING(e,o) (PRVM_GetString(prog, e->fields.ip[o]))

extern int prvm_type_size[8]; // for consistency : I think a goal of this sub-project is to
// make the new vm mostly independent from the old one, thus if it's necessary, I copy everything

void PRVM_Init_Exec(prvm_prog_t *prog);

void PRVM_ED_PrintEdicts_f(struct cmd_state_s *cmd);
void PRVM_ED_PrintNum (prvm_prog_t *prog, int ent, const char *wildcard_fieldname);

const char *PRVM_GetString(prvm_prog_t *prog, int num);
int PRVM_SetEngineString(prvm_prog_t *prog, const char *s);
const char *PRVM_ChangeEngineString(prvm_prog_t *prog, int i, const char *s);
/// Takes an strlen (not a buffer size).
int PRVM_SetTempString(prvm_prog_t *prog, const char *s, size_t slen);
int PRVM_AllocString(prvm_prog_t *prog, size_t bufferlength, char **pointer);
void PRVM_FreeString(prvm_prog_t *prog, int num);

mdef_t *PRVM_ED_FieldAtOfs(prvm_prog_t *prog, unsigned int ofs);
qbool PRVM_ED_ParseEpair(prvm_prog_t *prog, prvm_edict_t *ent, mdef_t *key, const char *s, qbool parsebackslash);
char *PRVM_UglyValueString(prvm_prog_t *prog, etype_t type, prvm_eval_t *val, char *line, size_t linelength);
char *PRVM_GlobalString(prvm_prog_t *prog, int ofs, char *line, size_t linelength);
char *PRVM_GlobalStringNoContents(prvm_prog_t *prog, int ofs, char *line, size_t linelength);

//============================================================================

/*
Initializing a vm:
Call InitProg with the num
Set up the fields marked with [INIT] in the prog struct
Load a program with LoadProgs
*/
// Load expects to be called right after Reset
void PRVM_Prog_Init(prvm_prog_t *prog, struct cmd_state_s *cmd);
void PRVM_Prog_Load(prvm_prog_t *prog, const char *filename, unsigned char *data, fs_offset_t size, void CheckRequiredFuncs(prvm_prog_t *prog, const char *filename), int numrequiredfields, prvm_required_field_t *required_field, int numrequiredglobals, prvm_required_field_t *required_global);
void PRVM_Prog_Reset(prvm_prog_t *prog);

void PRVM_StackTrace(prvm_prog_t *prog);
void PRVM_Breakpoint(prvm_prog_t *prog, int stack_index, const char *text);
void PRVM_Watchpoint(prvm_prog_t *prog, int stack_index, const char *text, etype_t type, prvm_eval_t *o, prvm_eval_t *n);

void VM_Warning(prvm_prog_t *prog, const char *fmt, ...) DP_FUNC_PRINTF(2);

void VM_GenerateFrameGroupBlend(prvm_prog_t *prog, struct framegroupblend_s *framegroupblend, const prvm_edict_t *ed);
void VM_FrameBlendFromFrameGroupBlend(struct frameblend_s *frameblend, const struct framegroupblend_s *framegroupblend, const struct model_s *model, double curtime);
void VM_UpdateEdictSkeleton(prvm_prog_t *prog, prvm_edict_t *ed, const struct model_s *edmodel, const struct frameblend_s *frameblend);
void VM_RemoveEdictSkeleton(prvm_prog_t *prog, prvm_edict_t *ed);

void PRVM_ExplicitCoverageEvent(prvm_prog_t *prog, mfunction_t *func, int statement);

#endif
