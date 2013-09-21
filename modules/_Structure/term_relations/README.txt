
## SUMMARY ##

This module enhances support for related terms. It recognises term relationships as a first class feature of a taxonomy that deserves special treatment. This module provides the following:

- Directed relationships - preserve the direction of term relationships.
- Cross-vocabulary relationships - allow terms to relate to terms in other vocabularies.
- D7 support - will carry support for related terms through to Drupal 7 and possibly integrate core related terms with the field API.
- A replacement for taxonomy_get_related() - handles directed relationships, cross vocabulary relationships, and will be available in D7.
- Related term management via Taxonomy Manager - browse and create term relationships in the Double Tree view and in the term edit popups.

NOTE: When using related terms in D6 you should be aware of this issue - http://drupal.org/node/251255 - and if necessary apply this patch here http://drupal.org/node/251255#comment-3691050 to avoid losing your relationship data.


## FEATURES ##


### Directed relationships ###

Preserve the direction of term relationships. Whilst the core data model supports directed relationships, the taxonomy.module code does not. Specifically: taxonomy_save_term() effectively re-saves right to left relationships as left to right relationships; and taxonomy_get_related() returns all relationships irrespective of direction. This module introduces a new function to get directed relationships, and preserves relationship direction via hooks. As there is no way to stop taxonomy_save_term() destroying the relationship direction, hooks into forms that call taxonomy_save_term() are used to save and subsequently restore the relationship direction. A patch to core would be ideal, but being pragmatic, and considering the lack of support for related terms in D7, using available hooks seems like the best approach.

#### Why not patch core? ####
Existing behaviour, that relationships are bidirectional, is expected behaviour, and would have to remain the default behaviour. To treat term relationships as uni-directional would require an additional site wide or per-vocabulary configuration option - i.e. new functionality with no chance of being committed to Drupal 6.


### Cross vocabulary relations ###

Allow terms from one vocabulary to be related to terms in another vocabulary. There is an existing module that introduced this concept - Taxonomy Vocab Relate. For several reasons the functionality of that module has been replicated and enhanced in this project.


### Restoration of related term support in Drupal 7 ###

Related terms have been dropped from core in Drupal 7 on the justification that the field API can better provide related term functionality. Whilst I understand the appeal of fields in adding properties to terms, I believe their use should be reserved for arbitrary properties rather than fundamentally structural properties - i.e. related terms, synonyms, and term hierarchy. In Drupal 7, term hierarchy is treated as a fundamental property of a taxonomy, but term relationships are not. Personally I can see no reason for this inconsistency (parents are a type of relationship) other than that hierarchical taxonomies are much more common than taxonomies that contain related terms.

Whilst I disagree with the principle of dropping related term support from core, there probably use cases where the field API should be used, either as a direct replacement for core support or perhaps as a flexible means to expose the related term data held in core.

#### Pros and cons of using fields for related terms ####
Pros:
- More flexible.
- Built in support for views etc.
- Possible to define different fields for different types of relationship.
- Need for contrib modules lessened by increased flexibility of relation fields.

Cons:
- Requires admin set up - possibility for relations to be set up in many different and un-desirable ways.
- Not easy for contrib modules to depend on relations field(s) without extra configuration step and even then no guarantee that relations fields are usable. Although need for contrib modules lessened by increased flexibility of relation fields (added to pros).
- Lack of portability of terms between hierarchies. Possibly require mapping of structural fields.
- Relationships may be defined in different fields. Harder to get the set of all relationships.
- No possibility for clear policy on directed relationships.


### Taxonomy Manager support ###

For managing relationships between terms in different vocabularies the Double Tree view of Taxonomy Manager proves to be ideal.


## USAGE ##

This module provides a single administration setting at Administer > Site Configuration > Term Relations. If the 'directed relationships' checkbox is set, then the direction of relationships is preserved. In addition, only left-to-right relationships are displayed on the term edit, and term_relations_get_related() will by default return only left to right related terms.


## API ##

- term_relations_get_related($tid, $key = 'tid', $vid = 'all', $direction = NULL);
- term_relations_is_directed();


## INSPIRATION ##

- The lack of core support for term relations in D7.
- Notes regarding definitions of vocabularies, taxonomies, ontologies etc - http://infogrid.org/wiki/Reference/PidcockArticle.

## CONTACT ##

- Andy Chapman (chaps2)