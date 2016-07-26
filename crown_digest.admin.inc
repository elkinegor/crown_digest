<?php
function crown_digest_config($form, &$form_state)
{
  $form = array();
  $form['mail_template'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mail template') ,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['mail_template']['crown_digest_email_title'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail title') ,
    '#default_value' => variable_get('crown_digest_email_title', '') ,
    '#required' => TRUE,
  );
  $form['mail_template']['crown_digest_email_body'] = array(
    '#type' => 'textarea',
    '#title' => t('E-mail body') ,
    '#default_value' => variable_get('crown_digest_email_body', '') ,
    '#required' => TRUE,
    '#description' => '
      [todays:date] - current date<br />
      [requests_list] - list of requests<br />
      [username] - user real name
    ',
    '#rows' => 28,
  );
  $form['mail_template']['crown_digest_email_body_row'] = array(
    '#type' => 'textarea',
    '#title' => t('E-mail row code') ,
    '#default_value' => variable_get('crown_digest_email_body_row', '') ,
    '#required' => TRUE,
    '#description' => '
      [nid] - Node id<br />
      [attention] - Attention level (Link to term)<br />
      [pic] - user avatar (link to user)<br />
      [user_name] - user first name from adress field<br />
      [date_ago] - date<br />
      [access_points] - userpoints from request<br />
      [purpose]<br />
      [title_link] - lint to request page<br />
      [amount] - request amount
    ',
    '#rows' => 10,
  );
  $form['crown_digest_test_is_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Test is active?') ,
    '#default_value' => variable_get('crown_digest_test_is_active', false) ,
  );
  $form['crown_digest_reset_time'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reset time and digest active?') ,
    '#default_value' => variable_get('crown_digest_reset_time', false) ,
  );
  $form['crown_digest_report'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sent report to test mail') ,
    '#default_value' => variable_get('crown_digest_report', false) ,
  );
  $form['crown_digest_test_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Test E-mail') ,
    '#default_value' => variable_get('crown_digest_test_email', '') ,
  );
  $form['crown_digest_submission_count'] = array(
    '#type' => 'textfield',
    '#title' => t('When digest should be send') ,
    '#default_value' => variable_get('crown_digest_submission_count', '10') ,
    '#required' => TRUE,
  );
  $form['crown_digest_mails_per_cron'] = array(
    '#type' => 'textfield',
    '#title' => t('How many messages will sent per cron') ,
    '#default_value' => variable_get('crown_digest_mails_per_cron', 10) ,
    '#required' => TRUE,
  );
  $form['crown_digest_taxonomy_machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Taxonomy vocabulary machine name with loan types') ,
    '#default_value' => variable_get('crown_digest_taxonomy_machine_name', '') ,
    '#required' => TRUE,
  );
  $form['crown_digest_delivery_machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Taxonomy vocabulary machine name with Digest Delivery') ,
    '#default_value' => variable_get('crown_digest_delivery_machine_name', '') ,
    '#required' => TRUE,
  );
  $form['crown_digest_delivery_loan_types_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Compare Loan types in Subscriber User profile and Request node') ,
    '#default_value' => variable_get('crown_digest_delivery_loan_types_check', false) ,
  );
  $taxonomy_machine_name = variable_get('crown_digest_taxonomy_machine_name', '');
  if ($taxonomy_machine_name != '') {
    $taxonomy_vocabulary = taxonomy_vocabulary_machine_name_load($taxonomy_machine_name);
    $terms = taxonomy_get_tree($taxonomy_vocabulary->vid);
    $loan_types = array();
    foreach($terms as $term) {
      $loan_types[$term->tid] = $term->name; 
    }
    $form['loan_types'] = array(
      '#type' => 'fieldset',
      '#title' => t('Select loan types') ,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE, 
    );
    $form['loan_types']['crown_digest_loan_types'] = array(
      '#type' => 'checkboxes',
      '#options' => $loan_types,
      '#title' => t('Select loan types') ,
      '#default_value' => variable_get('crown_digest_loan_types', array()) ,
      '#required' => TRUE,
    );
  }
  $form['content_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select content types') ,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['content_types']['crown_digest_content_types'] = array(
    '#type' => 'checkboxes',
    '#options' => node_type_get_names() ,
    '#title' => t('Select content types') ,
    '#default_value' => variable_get('crown_digest_content_types', array()) ,
    '#required' => TRUE,
  );
  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select user roles') ,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['roles']['crown_digest_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => user_roles(true) ,
    '#title' => t('Select user roles') ,
    '#default_value' => variable_get('crown_digest_roles', array()) ,
    '#required' => TRUE,
  );
  $form['crown_digest_last_time'] = array(
    '#markup' => 'Last time ' . variable_get('crown_digest_last_time', 'not set') . " (" . date("d.m.Y", variable_get('crown_digest_last_time', 'not set')) . ")" . '<br />',
  );
  $form['crown_digest_active'] = array(
    '#markup' => 'Digest active ' . variable_get('crown_digest_active', 'not set') . '<br />',
  );
  $form['markup'] = array(
    '#markup' => l("Run Digest", "admin/config/crown/crown_digest_run") ,
  );
  if (variable_get('crown_digest_reset_time', false)) {
    variable_set('crown_digest_last_time', 0);
    variable_set('crown_digest_reset_time', false);
    variable_set('crown_digest_active', 0);
  }
  return system_settings_form($form);
}