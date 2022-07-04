
import pandas as pd

parquetFileName="vijno.parquet"

filterList=[
('id','in',[ 'd45333' ]),
('name','in',[ 'vinoth' ]),
('age','in',[ 10 ])
]


parquetFile = pd.read_parquet(parquetFileName, engine='pyarrow',filters=filterList)

parquetFile.to_csv("/vinoth/v6Temp/parquetToCsvFile.csv")
