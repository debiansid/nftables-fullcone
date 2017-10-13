/*
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#include <config.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include <netlink.h>
#include <gmputil.h>
#include <erec.h>

static const struct input_descriptor internal_indesc = {
	.type	= INDESC_INTERNAL,
	.name	= "internal",
};

const struct location internal_location = {
	.indesc	= &internal_indesc,
};

static const char * const error_record_names[] = {
	[EREC_INFORMATIONAL]	= NULL,
	[EREC_WARNING]		= "Warning",
	[EREC_ERROR]		= "Error"
};

static void input_descriptor_destroy(const struct input_descriptor *indesc)
{
	if (indesc->location.indesc &&
	    indesc->location.indesc->type != INDESC_INTERNAL) {
		input_descriptor_destroy(indesc->location.indesc);
	}
	if (indesc->name)
		xfree(indesc->name);
	xfree(indesc);
}

static struct input_descriptor *input_descriptor_dup(const struct input_descriptor *indesc)
{
	struct input_descriptor *dup_indesc;

	dup_indesc = xmalloc(sizeof(struct input_descriptor));
	*dup_indesc = *indesc;

	if (indesc->location.indesc &&
	    indesc->location.indesc->type != INDESC_INTERNAL)
		dup_indesc->location.indesc = input_descriptor_dup(indesc->location.indesc);

	if (indesc->name)
		dup_indesc->name = xstrdup(indesc->name);

	return dup_indesc;
}

void erec_add_location(struct error_record *erec, const struct location *loc)
{
	assert(erec->num_locations < EREC_LOCATIONS_MAX);
	erec->locations[erec->num_locations] = *loc;
	erec->locations[erec->num_locations].indesc = input_descriptor_dup(loc->indesc);
	erec->num_locations++;
}

void erec_destroy(struct error_record *erec)
{
	unsigned int i;

	xfree(erec->msg);
	for (i = 0; i < erec->num_locations; i++) {
		input_descriptor_destroy(erec->locations[i].indesc);
	}
	xfree(erec);
}

__attribute__((format(printf, 3, 0)))
struct error_record *erec_vcreate(enum error_record_types type,
				  const struct location *loc,
				  const char *fmt, va_list ap)
{
	struct error_record *erec;

	erec = xmalloc(sizeof(*erec));
	erec->type		= type;
	erec->num_locations	= 0;
	erec_add_location(erec, loc);

	if (vasprintf(&erec->msg, fmt, ap) < 0)
		erec->msg = NULL;

	return erec;
}

__attribute__((format(printf, 3, 4)))
struct error_record *erec_create(enum error_record_types type,
				 const struct location *loc,
				 const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	va_start(ap, fmt);
	erec = erec_vcreate(type, loc, fmt, ap);
	va_end(ap);
	return erec;
}

void erec_print(struct output_ctx *octx, const struct error_record *erec,
		unsigned int debug_mask)
{
	const struct location *loc = erec->locations, *iloc;
	const struct input_descriptor *indesc = loc->indesc, *tmp;
	const char *line = NULL; /* silence gcc */
	char buf[1024] = {};
	char *pbuf = NULL;
	unsigned int i, end;
	int l, ret;
	off_t orig_offset = 0;
	FILE *f = octx->output_fp;

	if (!f)
		return;

	switch (indesc->type) {
	case INDESC_BUFFER:
	case INDESC_CLI:
		line = indesc->data;
		*strchrnul(line, '\n') = '\0';
		break;
	case INDESC_FILE:
		orig_offset = ftell(indesc->fp);
		fseek(indesc->fp, loc->line_offset, SEEK_SET);
		ret = fread(buf, 1, sizeof(buf) - 1, indesc->fp);
		if (ret > 0)
			*strchrnul(buf, '\n') = '\0';
		line = buf;
		fseek(indesc->fp, orig_offset, SEEK_SET);
		break;
	case INDESC_INTERNAL:
	case INDESC_NETLINK:
		break;
	default:
		BUG("invalid input descriptor type %u\n", indesc->type);
	}

	if (indesc->type == INDESC_NETLINK) {
		fprintf(f, "%s: ", indesc->name);
		if (error_record_names[erec->type])
			fprintf(f, "%s: ", error_record_names[erec->type]);
		fprintf(f, "%s\n", erec->msg);
		for (l = 0; l < (int)erec->num_locations; l++) {
			loc = &erec->locations[l];
			netlink_dump_expr(loc->nle, f, debug_mask);
		}
		fprintf(f, "\n");
	} else {
		if (indesc->location.indesc != NULL) {
			const char *prefix = "In file included from";
			iloc = &indesc->location;
			for (tmp = iloc->indesc;
			     tmp != NULL && tmp->type != INDESC_INTERNAL;
			     tmp = iloc->indesc) {
				fprintf(f, "%s %s:%u:%u-%u:\n", prefix,
					tmp->name,
					iloc->first_line, iloc->first_column,
					iloc->last_column);
				prefix = "                 from";
				iloc = &tmp->location;
			}
		}
		if (indesc->name != NULL)
			fprintf(f, "%s:%u:%u-%u: ", indesc->name,
				loc->first_line, loc->first_column,
				loc->last_column);
		if (error_record_names[erec->type])
			fprintf(f, "%s: ", error_record_names[erec->type]);
		fprintf(f, "%s\n", erec->msg);

		if (indesc->type != INDESC_INTERNAL)
			fprintf(f, "%s\n", line);

		end = 0;
		for (l = erec->num_locations - 1; l >= 0; l--) {
			loc = &erec->locations[l];
			end = max(end, loc->last_column);
		}
		pbuf = xmalloc(end + 1);
		memset(pbuf, ' ', end + 1);
		for (l = erec->num_locations - 1; l >= 0; l--) {
			loc = &erec->locations[l];
			for (i = loc->first_column ? loc->first_column - 1 : 0;
			     i < loc->last_column; i++)
				pbuf[i] = l ? '~' : '^';
		}
		pbuf[end] = '\0';
		fprintf(f, "%s", pbuf);
		xfree(pbuf);
	}
	fprintf(f, "\n");
}

void erec_print_list(struct output_ctx *octx, struct list_head *list,
		     unsigned int debug_mask)
{
	struct error_record *erec, *next;

	list_for_each_entry_safe(erec, next, list, list) {
		list_del(&erec->list);
		erec_print(octx, erec, debug_mask);
		erec_destroy(erec);
	}
}

int __fmtstring(4, 5) __stmt_binary_error(struct eval_ctx *ctx,
					  const struct location *l1,
					  const struct location *l2,
					  const char *fmt, ...)
{
	struct error_record *erec;
	va_list ap;

	va_start(ap, fmt);
	erec = erec_vcreate(EREC_ERROR, l1, fmt, ap);
	if (l2 != NULL)
		erec_add_location(erec, l2);
	va_end(ap);
	erec_queue(erec, ctx->msgs);
	return -1;
}
