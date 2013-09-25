<?php

/**
 * @file
 * Module constants list.
 */

// Ratings titles.
define('PRICE', 'Price Value');
define('FEATURES', 'Features');
define('RELY', 'Reliability & Uptime');
define('CUSTOMER', 'Customer Support');
define('CONTROL', 'Control Panel Use');

define('OVERALL', 'Overall Average Rating');

define('RECOMMEND', 'Would you recommend this web host?');



// Fields hints.
define('FNAME_HINT', 'First');
define('LNAME_HINT', 'Last');
define('EMAIL_HINT', 'Enter a valid email');
define('PROS_HINT', 'Optional');
define('CONS_HINT', 'Optional');

// Provider data
//$service_types = serialize(array('ch' => 'Cloud Hosting', 'mh' => 'Managed Hosting', 'vps' => 'VPS Hosting', 'ds' => 'Dedicated Servers', 'sh' => 'Shared Hosting', 'cb' => 'Cloud Backup'));
$service_types = serialize(array('wp' => 'WordPress', 'ch' => 'Cloud Hosting', 'vps' => 'VPS Hosting', 'ds' => 'Dedicated Servers', 'sh' => 'Shared Hosting'));

$service_descriptions = serialize(array('pti' => 'Plan title', 'sp' => 'Space', 'bw' => 'Bandwidth', 'vr-y' => 'Video Review (YouTube video ID)', 's-url' => 'Outbound Service Url', 'trend' => 'Trend'));
$fee_types = serialize(array('mon' => array('Monthly fees', '$'), 'set' => array('Setup fees', ''), 'oth' => array('Other fees', '') ));

define('SERVICE_TYPES', $service_types);
define('SERVICE_DESCRIPTIONS', $service_descriptions);
define('FEE_TYPES', $fee_types);


$provider_options = array(
          'Host Info' => array(
              'Year Founded' => 'textfield',
              'Headquarters Location' => 'textfield',
              'Service Type Availability' => 'textfield',
          ),
          
          'Services & Performance' => array(
              'Monthly Cost of Cheapest Service' => 'textfield',
              'Requires Contract' => 'checkbox',
              'Money Back Guarantee' => 'textfield',
              'Managed Support Included' => 'checkbox',
              'Managed Backup' => 'checkbox',
              '3rd Party Application Support' => 'checkbox',
              'Maximum Memory' => 'textfield',
              'Maximum Speed' => 'textfield',
              'Maximum Storage' => 'textfield',
              'Domains Allowed' => 'checkbox',
              'Control Panel' => 'checkbox',
              'SLA for Network Uptime' => 'textfield',
              'SLA for Infrastructure Uptime' => 'textfield',
          ),

          
          'Security' => array(
              'Firewall Zones' => 'checkbox',
              'Network Isolation' => 'checkbox',
              'Web Application Protection' => 'checkbox',
              'DDos Protection' => 'checkbox',
              'Secure VPN Access' => 'checkbox',
              'VMware Based' => 'checkbox',
          ),
          
          'Support' => array(
              'Hours' => 'textfield',
              'Telephone Support' => 'checkbox',
              'Email Support' => 'checkbox',
              'Instant Chat' => 'checkbox',
              '24/7 Call-in Support' => 'checkbox',
              'FAQs Section' => 'checkbox',
              'Video Tutorials' => 'checkbox',
              'E-Guides' => 'checkbox',
              'Online Ticket Submissions' => 'checkbox',
        ),
          
      );
      
define('PROVIDER_OPTIONS', serialize($provider_options));