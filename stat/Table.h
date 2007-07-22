#ifndef _Table_h_
#define _Table_h_
/* Table.h
 *
 * Copyright (C) 2002-2007 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * pb 2007/06/28
 */

#ifndef _Collection_h_
	#include "Collection.h"
#endif
#ifndef _Graphics_h_
	#include "Graphics.h"
#endif

/* For the inheritors. */
#include "Table_def.h"
#define TableRow_methods Data_methods
oo_CLASS_CREATE (TableRow, Data);
#define Table_members Data_members \
	long numberOfColumns; \
	struct TableColumnHeader *columnHeaders; \
	Ordered rows;
#define Table_methods Data_methods
oo_CLASS_CREATE (Table, Data);

int Table_initWithColumnNames (I, long numberOfRows, const char *columnNames);
Table Table_createWithColumnNames (long numberOfRows, const char *columnNames);
int Table_initWithoutColumnNames (I, long numberOfRows, long numberOfColumns);
Table Table_createWithoutColumnNames (long numberOfRows, long numberOfColumns);
#define Table_create Table_createWithoutColumnNames
int Table_appendRow (Table me);
int Table_appendColumn (Table me, const char *label);
int Table_appendSumColumn (Table me, long column1, long column2, const char *label);
int Table_appendDifferenceColumn (Table me, long column1, long column2, const char *label);
int Table_appendProductColumn (Table me, long column1, long column2, const char *label);
int Table_appendQuotientColumn (Table me, long column1, long column2, const char *label);
int Table_removeRow (Table me, long row);
int Table_removeColumn (Table me, long column);
int Table_insertRow (Table me, long row);
int Table_insertColumn (Table me, long column, const char *label);
void Table_setColumnLabel (Table me, long column, const char *label);
long Table_columnLabelToIndex (Table me, const char *label);
long Table_searchColumn (Table me, long column, const char *value);

/*
 * Procedure for reading strings or numbers from table cells:
 * use the following two calls exclusively.
 */
const char * Table_getStringValue (Table me, long row, long column);
double Table_getNumericValue (Table me, long row, long column);

/*
 * Procedure for writing strings or numbers into table cells:
 * use the following two calls exclusively.
 */
int Table_setStringValue (Table me, long row, long column, const char *value);
int Table_setNumericValue (Table me, long row, long column, double value);

/* For optimizations only (e.g. conversion to Matrix or TableOfReal). */
void Table_numericize (Table me, long column);

double Table_getQuantile (Table me, long column, double quantile);
double Table_getMean (Table me, long column);
double Table_getGroupMean (Table me, long column, long groupColumn, const char *group);
double Table_getStdev (Table me, long column);
double Table_getCorrelation_pearsonR (Table me, long column1, long column2, double significanceLevel,
	double *out_significance, double *out_lowerLimit, double *out_upperLimit);
double Table_getCorrelation_kendallTau (Table me, long column1, long column2, double significanceLevel,
	double *out_significance, double *out_lowerLimit, double *out_upperLimit);
double Table_getMean_studentT (Table me, long column, double significanceLevel,
	double *out_tFromZero, double *out_significanceFromZero, double *out_lowerLimit, double *out_upperLimit);
double Table_getDifference_studentT (Table me, long column1, long column2, double significanceLevel,
	double *out_t, double *out_significance, double *out_lowerLimit, double *out_upperLimit);
double Table_getGroupMean_studentT (Table me, long column, long groupColumn, const char *group1, double significanceLevel,
	double *out_tFromZero, double *out_significanceFromZero, double *out_lowerLimit, double *out_upperLimit);
double Table_getGroupDifference_studentT (Table me, long column, long groupColumn, const char *group1, const char *group2, double significanceLevel,
	double *out_tFromZero, double *out_significanceFromZero, double *out_lowerLimit, double *out_upperLimit);
double Table_getVarianceRatio (Table me, long column1, long column2, double significanceLevel,
	double *out_significance, double *out_lowerLimit, double *out_upperLimit);

int Table_formula (Table me, long column, const char *formula);
int Table_formula_columnRange (Table me, long column1, long column2, const char *expression);

Table Tables_append (I, thou);
Table Tables_appendMany (Collection me);

void Table_sortRows (Table me, long *columns, long numberOfColumns);
int Table_sortRows_string (Table me, const char *columns_string);

void Table_scatterPlot (Table me, Graphics g, long xcolumn, long ycolumn,
	double xmin, double xmax, double ymin, double ymax, long markColumn, int fontSize, int garnish);
void Table_scatterPlot_mark (Table me, Graphics g, long xcolumn, long ycolumn,
	double xmin, double xmax, double ymin, double ymax, double markSize_mm, const char *mark, int garnish);
void Table_drawEllipse (Table me, Graphics g, long xcolumn, long ycolumn,
	double xmin, double xmax, double ymin, double ymax, double numberOfSigmas, int garnish);

void Table_list (Table me, bool includeRowNumbers);
int Table_writeToTableFile (Table me, MelderFile file);
Table Table_readFromTableFile (MelderFile file);
Table Table_readFromCharacterSeparatedTextFile (MelderFile file, char separator);

Table Table_extractRowsWhereColumn_number (Table me, long column, int which_Melder_NUMBER, double criterion);
Table Table_extractRowsWhereColumn_string (Table me, long column, int which_Melder_STRING, const char *criterion);
Table Table_collapseRows (Table me, const char *factors_string, const char *columnsToSum_string,
	const char *columnsToAverage_string, const char *columnsToMedianize_string,
	const char *columnsToAverageLogarithmically_string, const char *columnsToMedianizeLogarithmically_string);
Table Table_rowsToColumns (Table me, const char *factors_string, long columnToTranspose, const char *columnsToExpand_string);

#endif
/* End of file Table.h */
