<?php

include "dbaccess_header.php";

$sql = <<<SQL
select
  year(l.success_datetime) as Year,
  monthname(l.success_datetime) as Month,
  count(*) as "Items vended",
  count(IF(l.vmc_id = 1, 1, NULL)) as "Snacks Vended",
  count(IF(l.vmc_id = 4, 1, NULL)) as "Drinks Vended",
  concat('£', cast((sum(l.amount_scaled)/100) as decimal(20,2))) as "Vend value",
  concat('£', cast((avg(l.amount_scaled)/100) as decimal(20,2))) as "Avg item cost",
  (
    select concat('£', cast((sum(-1*t.amount)/100) as decimal(20,2)))
    from transactions t
    where year(l.success_datetime) = year(t.transaction_datetime)
      and month(l.success_datetime) = month(t.transaction_datetime)
      and t.transaction_status = 'COMPLETE'
      and t.transaction_type = 'TOOL'
  ) as "Laser charges",
  (
    select concat('£', cast((sum(t.amount)/100) as decimal(20,2)))
    from transactions t
    where year(l.success_datetime) = year(t.transaction_datetime)
      and month(l.success_datetime) = month(t.transaction_datetime)
      and t.amount > 0
      and t.transaction_status = 'COMPLETE'
  ) as "Payments"
from vend_log l
where (l.vmc_id in (1, 4) or l.vmc_id is null)
  and l.success_datetime is not null
  and (year(l.success_datetime) > 2012 or (year(l.success_datetime)=2012 and month(l.success_datetime) >= 6))
group by year(l.success_datetime), monthname(l.success_datetime)
order by year(l.success_datetime) desc, month(l.success_datetime) desc;
SQL;

print sql_to_tt_json(db_pdo_link(), $sql);

?>
