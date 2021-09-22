#GH_PY_SAM_2

import pandas as pd
df = pd.read_parquet('<parquet_path>/par3a3a6.parquet')
df.to_csv('filename.csv')
