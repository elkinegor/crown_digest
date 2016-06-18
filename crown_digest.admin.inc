<?php



function crown_digest_config($form, &$form_state) {

  $form = array(); 

 

  $form['crown_digest_email_title'] = array(

    '#type' => 'textfield', 

    '#title' => t('E-mail title'),

    '#default_value' => variable_get('crown_digest_email_title', ''),

    '#required' => TRUE,

  );

  $form['crown_digest_email_body'] = array( 

    '#type' => 'textarea',

    '#title' => t('E-mail body'),

    '#default_value' => variable_get('crown_digest_email_body', ''),

    '#required' => TRUE,
    '#description' => '
      [todays:date] - current date<br />
      [requests_list] - list of requests<br />
      [username] - user real name
    ',
    '#rows' => 28,

  );

  $form['crown_digest_email_body_row'] = array( 

    '#type' => 'textarea',

    '#title' => t('E-mail row code'),

    '#default_value' => variable_get('crown_digest_email_body_row', ''),

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

    '#title' => t('Test is active?'),

    '#default_value' => variable_get('crown_digest_test_is_active', false),

  );

  $form['crown_digest_reset_time'] = array(

    '#type' => 'checkbox', 

    '#title' => t('Reset time and digest active?'),

    '#default_value' => variable_get('crown_digest_reset_time', false),

  );

  $form['crown_digest_report'] = array(

    '#type' => 'checkbox', 

    '#title' => t('Sent report to test mail'),

    '#default_value' => variable_get('crown_digest_report', false),

  );

  $form['crown_digest_test_email'] = array(

    '#type' => 'textfield', 

    '#title' => t('Test E-mail'),

    '#default_value' => variable_get('crown_digest_test_email', ''),

  );

  $form['crown_digest_submission_count'] = array(

    '#type' => 'textfield',

    '#title' => t('When digest should be send'),

    '#default_value' => variable_get('crown_digest_submission_count', '10'),

    '#required' => TRUE,

  );

  $form['crown_digest_mails_per_cron'] = array( 

    '#type' => 'textfield',

    '#title' => t('How many messages will sent per cron'),

    '#default_value' => variable_get('crown_digest_mails_per_cron', 10),

    '#required' => TRUE,

  );

  $terms = taxonomy_get_tree(3);

  $loan_types = array();

  foreach ($terms as $term) {

    $loan_types[$term->tid] = $term->name;

  }



  $form['crown_digest_loan_types'] = array( 

    '#type' => 'checkboxes',

    '#options' => $loan_types,

    '#title' => t('Select loan types'),

    '#default_value' => variable_get('crown_digest_loan_types', array()),

    '#required' => TRUE,

  );



  $form['crown_digest_content_types'] = array( 

    '#type' => 'checkboxes',

    '#options' => node_type_get_names(),

    '#title' => t('Select content types'),

    '#default_value' => variable_get('crown_digest_content_types', array()),

    '#required' => TRUE,

  );

  $form['crown_digest_roles'] = array( 

    '#type' => 'checkboxes',

    '#options' => user_roles(true),

    '#title' => t('Select user roles'),

    '#default_value' => variable_get('crown_digest_roles', array()),

    '#required' => TRUE,

  );

  $form['crown_digest_last_time'] = array( 

    '#markup' => 'Last time '.variable_get('crown_digest_last_time', 'not set') . '<br />',

  );

  $form['crown_digest_active'] = array( 

    '#markup' => 'Digest active '.variable_get('crown_digest_active', 'not set'),

  ); 



  if (variable_get('crown_digest_reset_time', false)) {

    variable_set('crown_digest_last_time', 0);

    variable_set('crown_digest_reset_time', false);

    variable_set('crown_digest_active', 0);

  }



  crown_digest_check();  



  return system_settings_form($form);

}



