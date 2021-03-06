drop table if exists pins;

create table pins 
(
  pin_id       int not null auto_increment,
  pin          varchar(12),
  date_added   timestamp default CURRENT_TIMESTAMP,
  expiry       timestamp NULL default NULL,
  state        int,
  member_id    int default NULL,
  constraint pins_pin unique (pin),
  primary key (pin_id)
) ENGINE = InnoDB; 

/*
 pin states:
  10 = Active
  20 = Expired
  30 = Cancelled
  40 = Enroll
*/