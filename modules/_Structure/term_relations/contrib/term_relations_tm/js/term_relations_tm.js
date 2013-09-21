
/**
 * @file
 * Expanding tree view - attach a callback to the click event which
 * runs after the tm click but before the term is expanded. As Drupal.attachBehaviours
 * is not called on the new elements - we have to be a bit more creative...
 */

/**
 * Adds relationship flags with click event to term labels in the tree structure.
 * The click event reveals and highlights related terms in the opposite tree.
 */
Drupal.attachRelationships = function(ul, tree) {
  $('li.has-related:not(.l2r,.r2l,.bi) > .term-line label', ul).append('<span class="has-related-flag">r</span>');
  $('li.has-related.l2r > .term-line label', ul).append('<span class="has-related-flag">r -></span>');
  $('li.has-related.r2l > .term-line label', ul).append('<span class="has-related-flag">r <-</span>');
  $('li.has-related.bi > .term-line label', ul).append('<span class="has-related-flag">r <></span>');
  $('li.has-related > .term-line label .has-related-flag', ul).click(function() {
    var li = $(this).parents("li:first");
    var tid = Drupal.getTermId(li);
    // get related - no reliable way to get the related tids - would put a map in settings but would need to change child form gets returns etc.
    var params = {};
    params['selected_terms['+ tid +']'] = tid;
    params['voc2'] = tree.otherTree.vocId;
    params['op'] = 'show_relations';

    $.ajax({
      data: params,
      type: "POST",
      url: Drupal.settings.DoubleTree['url'],
      dataType: 'json',
      success: function(response, status) {
        var allRelatedTids = [];

        for (var i in response.related_tids) {
          allRelatedTids = allRelatedTids.concat(response.related_tids[i]);
        }

        tree.otherTree.loadRootForm(allRelatedTids);
        $("#"+ tree.treeId).find(".highlightActiveTerm").removeClass('highlightActiveTerm');
        Drupal.activeTermSwapHighlight($('> .term-line a.term-data-link', li));
      }
    });

    return false;
  });
}

/**
 * Handle the 'show relations' double tree operation.
 */
Drupal.DoubleTree.prototype.showRelations = function(relatedTids) {
  var doubleTree = this;
  var allRelatedTids = [];
  var selectedTids = [];

  for (var i in relatedTids) {
    allRelatedTids = allRelatedTids.concat(relatedTids[i]);
  }

  for (var i in this.selected_terms) {
   selectedTids.push(Drupal.getTermId(this.selected_terms[i]));
  }

  if (doubleTree.direction == 'right-to-left') {
    doubleTree.leftTree.loadRootForm(allRelatedTids);
    doubleTree.rightTree.loadRootForm(selectedTids);
  }
  else {
    doubleTree.rightTree.loadRootForm(allRelatedTids);
    doubleTree.leftTree.loadRootForm(selectedTids);
  }
}

/*****************************************************************************
 * TaxonomyManagerTree prototype overrides.
 * This is the easiest way of getting extra params into AJAX callbacks, and
 * doing extra processing on success.
 * @todo - look for possible extension points and propose patch to TM.
 ****************************************************************************/

/**
 * Our own version of loadChildForm....
 * loads child terms and appends html to list
 * adds treeview, weighting etc. js to inserted child list
 */
Drupal.TaxonomyManagerTree.prototype.loadChildForm = function(li, update, callback) {
  var tree = this;
  if ($(li).is(".has-children") || update == true) {
    $(li).removeClass("has-children");
    if (update) {
      $(li).children("ul").remove();
    }
    var parentId = Drupal.getTermId(li);
    if (!(Drupal.settings.childForm['url'] instanceof Array)) {
      url = Drupal.settings.childForm['url'];
    }
    else {
      url = Drupal.settings.childForm['url'][0];
    }
    url += '/'+ this.treeId +'/'+ this.vocId +'/'+ parentId;
    var param = new Object();
    param['form_build_id'] = this.form_build_id;
    param['form_id'] = this.form_id;
    param['tree_id'] = this.treeId;
    param['language'] = this.language;

    // ******* Start of additional code *******
    // if in double tree context attach relationships
    if(this.otherTree) {
      param['relations_vid'] = this.otherTree.vocId;
    }
    // ******* End of additional code *********

    $.get(url, param, function(data) {
      $(li).append(data);
      var ul = $(li).children("ul");
      tree.attachTreeview(ul);
      tree.attachSiblingsForm(ul);
      tree.attachSelectAllChildren(ul);

      //only attach other features if enabled!
      var weight_settings = Drupal.settings.updateWeight || [];
      if (weight_settings['up']) {
        Drupal.attachUpdateWeightTerms(li);
      }
      var term_data_settings = Drupal.settings.termData || [];
      if (term_data_settings['url']) {
        Drupal.attachTermDataLinks(ul, tree);
      }

      // ******* Start of additional code *******
      Drupal.attachRelationships(ul,tree);
      // ******* End of additional code *********

      if (typeof(callback) == "function") {
        callback(li, tree);
      }
    });
  }
}

/**
 * function for reloading root tree elements
 */
Drupal.TaxonomyManagerTree.prototype.loadRootForm = function(tid) {
  if (!(Drupal.settings.childForm['url'] instanceof Array)) {
    url = Drupal.settings.childForm['url'];
  }
  else {
    url = Drupal.settings.childForm['url'][0];
  }
  var tree = this;
  url += '/'+ this.treeId +'/'+ this.vocId +'/0/'+ tid;


  var param = new Object();
    param['form_build_id'] = this.form_build_id;
    param['form_id'] = this.form_id;
    param['tree_id'] = this.treeId;
    param['language'] = this.language;

    // ******* Start of additional code *******
    // if in double tree context attach relationships
    if(this.otherTree) {
      param['relations_vid'] = this.otherTree.vocId;
    }
    // ******* End of additional code *********


  $.get(url, param, function(data) {
    $('#'+ tree.treeId).html(data);
    var ul = $('#'+ tree.treeId).children("ul");
    tree.attachTreeview(ul);
    tree.attachSiblingsForm(ul);
    tree.attachSelectAllChildren(ul);
    Drupal.attachUpdateWeightTerms(ul);
    Drupal.attachTermDataLinks(ul, tree);

    // ******* Start of additional code *******
    Drupal.attachRelationships(ul,tree);
    // ******* End of additional code *********

    if (tid) {
      // ******** Start of replacement code ********
      // var termLink = $("#"+ tree.treeId).find(":input[value="+ tid +"]").parent().find("a.term-data-link");
      // Drupal.activeTermSwapHighlight(termLink);

      // this code handles highlighting of multiple terms.
      tid_str = new String(tid);
      tids = tid_str.split(',');
      $("#"+ tree.treeId).find(".highlightActiveTerm").removeClass('highlightActiveTerm');
      for(i in tids) {
        var inputs = $("#"+ tree.treeId).find("label.option > :input[value="+ tids[i] +"]");
        var termLink = $(inputs).parent().find("a.term-data-link");
        if(termLink != "") {
          $(termLink).parent().addClass('highlightActiveTerm')
        }
      }
      // ******** End of replacement code ********
    }

    var lang = $('#edit-'+ tree.treeId +'-language').val();
    if (lang != "" && lang != tree.langauge) {
      $(tree.div).parent().siblings("div.taxonomy-manager-tree-top").find("select.language-selector option[value="+ lang +"]").attr("selected", "selected");
    }
  });
}

/**
 * sends selected terms to the server and receives the response message
 */
Drupal.DoubleTree.prototype.send = function() {
  var doubleTree = this;

  $(this.selected_parents).each(function() {
    var tid = Drupal.getTermId(this);
    doubleTree.param['selected_parents['+ tid +']'] = tid;
  });

  $(this.selected_terms).each(function() {
    var tid = Drupal.getTermId(this);
    doubleTree.param['selected_terms['+ tid +']'] = tid;
    var parentID = Drupal.getParentId(this);
    if (typeof(parentID) == "undefined") {
      doubleTree.updateWholeTree = true;
    }
    doubleTree.param['selected_terms_parent['+ tid +']'] = parentID;
  });

  $.ajax({
    data: doubleTree.param,
    type: "POST",
    url: this.url,
    dataType: 'json',
    success: function(response, status) {
      if (doubleTree.param['op'] == "show_relations" || doubleTree.param['op'] == "relate") {
        doubleTree.showRelations(response.related_tids);
      }
      else {
        doubleTree.showMsg(response.data, response.type);
        if (response.type == "status" && (doubleTree.param['op'] == "move" || doubleTree.param['op'] == "switch")) {
          doubleTree.updateTrees();
        }
      }
    }
  });
}

/**
 * attaches click events to the operations and collects selected terms
 */
Drupal.DoubleTree.prototype.attachOperations = function() {
  var doubleTree = this;

  // ******* Start of additional code *******
  // set double tree context on each tree for child form loading
  if(doubleTree.leftTree && doubleTree.rightTree) {
    doubleTree.leftTree.otherTree = doubleTree.rightTree;
    doubleTree.leftTree.direction = "left-to-right";
    doubleTree.rightTree.otherTree = doubleTree.leftTree;
    doubleTree.rightTree.direction = "right-to-left";

    // attach relationships
    Drupal.attachRelationships(doubleTree.leftTree.ul, doubleTree.leftTree);
    Drupal.attachRelationships(doubleTree.rightTree.ul, doubleTree.rightTree);
  }
  // ******* End of additional code *******

  $('#taxonomy-manager-double-tree-operations :input').click(function() {
    doubleTree.selected_terms = new Array();
    doubleTree.selected_parents = new Array();
    doubleTree.param = new Object();

    var button_value = $(this).val();
    doubleTree.param['op'] = 'move';

    if (button_value == 'Move right' || button_value == "Switch right" || button_value == "Relate right" || button_value == "Show relations right") {
      doubleTree.direction = "left-to-right";
      doubleTree.selected_terms = doubleTree.leftTree.getSelectedTerms();
      doubleTree.selected_parents = doubleTree.rightTree.getSelectedTerms();
      doubleTree.param['voc1'] = doubleTree.leftTree.vocId;
      doubleTree.param['voc2'] = doubleTree.rightTree.vocId;
    }
    else {
      doubleTree.direction = "right-to-left";
      doubleTree.selected_parents = doubleTree.leftTree.getSelectedTerms();
      doubleTree.selected_terms = doubleTree.rightTree.getSelectedTerms();
      doubleTree.param['voc1'] = doubleTree.rightTree.vocId;
      doubleTree.param['voc2'] = doubleTree.leftTree.vocId;
    }

    if (button_value == "translation") {
     doubleTree.param['op'] = 'translation';
     if (doubleTree.selected_terms.length != 1 || doubleTree.selected_parents.length != 1) {
       doubleTree.showMsg(Drupal.t("Select one term per tree to add a new translation."), "error");
       return false;
     }
    }
    else if (button_value == "Switch right" || button_value == "Switch left") {
      doubleTree.param['op'] = 'switch';
      doubleTree.updateWholeTree = true;
    }
    else if (button_value == "Relate right" || button_value == "Relate left") {
      doubleTree.param['op'] = 'relate';
      doubleTree.updateWholeTree = false;
    }
    else if (button_value == "Show relations right" || button_value == "Show relations left") {
      doubleTree.param['op'] = 'show_relations';
      doubleTree.updateWholeTree = true;
    }

    if (doubleTree.selected_terms.length == 0) {
      doubleTree.showMsg(Drupal.t("No terms selected."), "error");
      return false;
    }
    doubleTree.send();
    return false;
  });
}










