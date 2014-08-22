---
layout: post
title: "Database learning note"
description: 
modified: 2014-07-19 21:46:02 +0800
category: 
tags: [database, coursera note]
image:
  feature: 19.jpg-clip.jpg
  credit: 
  creditlink: 
comments: true
share: true
alias: [/2014/07/19/Database learning note]
---

## Introduce to Database

<!--more-->
Database Management System(DBMS) provides：
effcient, reliable, convinient, and safe multi-user storage of and access to massive amount of persistent data.

## Seven Adjectives

1. Massive: handle data of terabyte scale, even terabyte everyday.  Memory are incrsing 
2. Persistent: the object is still the data.
3. Safe: hardware,software,power,user   ensure the data is consistant.
4. Multi-user: concurrency control.
5. Convinient: easy to use. 
- Physical data independence.
- high-level query language.
6. Efficient: three  most important property for the databases is first performence,second performance ,third performance. thousands of queries/operator per seconds.
7. Reliable: 99.99999% of the time is to guarantee the realty.

## Key concepts
- Data model : set of records, XML
- Schema versus data: 
- Data definition language(DDL): set up schema
- Data manipulation or query language

## key people
- DBMS implementer : bulids system
- Database designer: Establishes schema
- Database application developer: programs that operate an database
- Database administrator: Loads data, keeps runnig smoothly.