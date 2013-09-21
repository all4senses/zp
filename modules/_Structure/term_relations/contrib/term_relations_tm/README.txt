

## SUMMARY ##

This module extends Taxonomy Manager in the following ways:

- Displays term relationships in the Double Tree view. This works both with same vocabulary relationships and cross-vocabulary relationships.
- Allows creation of relationships in the Double Tree view between one or more terms either in the same vocabulary or different vocabularies.
- If directed relationships have been configured, the relationship identifier will include a direction indicator, and relationships may be either created left-to-right or right-to-left.


## USAGE ##

For cross vocabulary relationships, this module depends on Term Relations Vocab to establish which vocabularies may be related and in which directions.

When viewing a vocabulary with Taxonomy Manager, select the Double Tree view and select the vocabulary you wish to view and/or create relationships with. This may be the same vocabulary or a different vocabulary.


### Relationship indicators ###

Terms that have existing relationships with terms in the opposite vocabulary are appended with a highlighted 'r'. If the site is set up to respect relationship direction, there is a direction indicator after the 'r': either '->', '<-', or '<>' as follows:

- 'r ->' indicates a left to right relationship.
- 'r <-' indicates right to left relationship.
- 'r <>' indicates a bi-directional relationship.

Clicking on the relationship indicator will reveal and highlight the related term or terms in the related vocabulary.


### Relationship Double Tree operators ###

There are up to four relationship Double Tree operation buttons: relate right, relate left, show relations right, and show relations left. The availability of these operations depends on the 'directed relationships' setting and vocabulary relationship settings. Double Tree operations operate on selected terms - i.e. you need to select one or more terms via the term's checkbox.

The first two operations (relate right, relate left) will toggle the relationships of all selected terms in the vocabulary on the left hand side with all selected terms in the vocabulary on the right hand side. The toggle operation means that existing relationships with the same direction will be removed. It is possible to add left-to-right relationships with "relate right" and right-to-left relationships with "relate left" to the same term or terms. This will create bi-directional relationships which will be indicated with a 'r <>' indicator.

The last two (show relations right, show relations left) have similar functionality to clicking on a term's relationship indicator except that they allow more than one term's relationships to be viewed.


## ADMINISTRATION ##

You may toggle the display of relationship indicators via the Taxonomy Manager config page.


## IMPLEMENTATION ##

Most of the code in this module was originally developed as a patch for this issue - http://drupal.org/node/842734. For several reasons, but mainly due to the size of the patch, it's rather specialised use, and the deprecation of related terms in D7, I decided to turn the patch into an independent module.

It was not practical to add this module's functionality to Taxonomy Manager solely via hooks. Therefore menu callback and JS prototype overrides have been used. Whilst this approach works well, the drawbacks are that:

1. This module is very sensitive to changes to the Taxonomy Manager module. To help keep things in sync, the version numbers used for this module will match the version numbers of Taxonomy Manager. Only use the corresponding version of Taxonomy Manager with this module.

2. This module is unlikely to be compatible with any other module which overrides the same menu callbacks or JS prototypes. AFAIK there aren't any at the moment.

The code in term_relations_tm.tree.inc implements multiple term highlighting in the Taxonomy Manager tree view. It would be much better if it was implemented as a patch.


## CONTACT ##

Andy Chapman (chaps2)
