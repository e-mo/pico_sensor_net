#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sensors/sht30/sht30_wsi.h"

void sht30_wsi_init(sht30_wsi_t *sensor, uint i2c_index) {
	sensor_data_init(
			&sensor->header,
			SHT30,
			&sht30_wsi_pack,
			&sht30_wsi_read
	);

	sensor->i2c_index = i2c_index;
}

#define SHT30_PACKED_SIZE (sizeof (SENSOR_TYPE) + (sizeof (float) * 2))

int sht30_wsi_pack(
		struct _sensor_generic *sensor,
		uint8_t *buffer, 
		uint buffer_len
)
{
	sht30_wsi_t *sht30 = (sht30_wsi_t *)sensor;

	*((SENSOR_TYPE *)buffer) = (SENSOR_TYPE)sht30->header.type;
	buffer += sizeof (SENSOR_TYPE);
	memcpy(buffer, &sht30->reading.temperature, sizeof (float));
	buffer += sizeof (float);
	memcpy(buffer, &sht30->reading.humidity, sizeof (float));

	return SHT30_PACKED_SIZE;
}

bool sht30_wsi_read(struct _sensor_generic *sensor) {
	sht30_wsi_t *sht30 = (sht30_wsi_t *)sensor;

	return sht30_rp2040_read(sht30->i2c_index, &sht30->reading);
}

struct _sensor_generic *sht30_wsi_unpack(uint8_t *buffer) {
	sht30_wsi_t *sensor = malloc(sizeof *sensor);
	if (!sensor) return NULL;

	sht30_wsi_init(sensor, 0);

	buffer += sizeof (SENSOR_TYPE);
	memcpy(&sensor->reading.temperature, buffer, sizeof (float));
	buffer += sizeof (float);
	memcpy(&sensor->reading.humidity, buffer, sizeof (float));
	
	return (struct _sensor_generic *) sensor;
}
